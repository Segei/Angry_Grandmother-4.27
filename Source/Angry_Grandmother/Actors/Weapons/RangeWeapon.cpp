// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/RangeWeapon.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
ARangeWeapon::ARangeWeapon()
{
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	MeshWeapon = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh weapon");
	MeshWeapon->SetupAttachment(RootComponent);
	BarrelComponent = CreateDefaultSubobject<UWeaponBarrelComponent>("Barrel component");
	BarrelComponent->SetupAttachment(RootComponent);
	HitEffectComponent = CreateDefaultSubobject<UHitEffectComponent>("Hit effector");
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARangeWeapon::BeginPlay()
{
	Super::BeginPlay();
	DelayBetweenShoot = 1.f / RPM * 60.f;
	HitEffectComponent->InjectToBarrel(BarrelComponent);
	CanReload = true;
}

// Called every frame
void ARangeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(Shooting)
	{
		TryShoot();
	}
}

void ARangeWeapon::StartReload()
{
	if(!CanReload)
	{
		return;
	}
	CanShooting = false;
	CanReload = false;
	if (CurrentAdditionalAmmo <= 0)
	{
		return;
	}
	if (CurrentAmmoInMagazine > 0)
	{
		MeshWeapon->PlayAnimation(AnimationReloadNoEmpty, false);
	}
	else
	{
		MeshWeapon->PlayAnimation(AnimationReloadEmpty, false);
	}
}

void ARangeWeapon::EndReload()
{
	int32 tempCountAmmo = MaxAmmoInMagazine - CurrentAmmoInMagazine;
	if (tempCountAmmo < CurrentAdditionalAmmo)
	{
		CurrentAdditionalAmmo -= tempCountAmmo;
		CurrentAmmoInMagazine = MaxAmmoInMagazine;
	}
	else
	{
		CurrentAmmoInMagazine += CurrentAdditionalAmmo;
		CurrentAdditionalAmmo = 0;
	}
	if(OnChangeAmmoInMagazine.IsBound())
	{
		OnChangeAmmoInMagazine.Broadcast(CurrentAmmoInMagazine);
	}
	if(OnChangeAmmoInAdditionalAmmo.IsBound())
	{
		OnChangeAmmoInAdditionalAmmo.Broadcast(CurrentAdditionalAmmo);
	}
	ReadyToShoot = true;
	CanShooting = true;
	CanReload = true;
}

void ARangeWeapon::StartShooting()
{
	Shooting = true;
}

void ARangeWeapon::EndShooting()
{
	Shooting = false;
}

void ARangeWeapon::TryShoot()
{
	if (!ReadyToShoot || !CanShooting)
	{
		return;
	}
	if (CurrentAmmoInMagazine == 0)
	{
		UGameplayStatics::PlaySoundAtLocation(this, NoAmmo, GetActorLocation(), GetActorRotation());
		ReadyToShoot = false;
		return;
	}
	ReadyToShoot = false;
	CurrentAmmoInMagazine --;
	MeshWeapon->PlayAnimation(AnimationShoot, false);
	BarrelComponent->Shoot(Damage);
	OnShootRifle.Broadcast();
	if(OnChangeAmmoInMagazine.IsBound())
	{
		OnChangeAmmoInMagazine.Broadcast(CurrentAmmoInMagazine);
	}
	GetWorldTimerManager().SetTimer(ShootDelay, this, &ARangeWeapon::EndShoot, DelayBetweenShoot);
}

void ARangeWeapon::EndShoot()
{
	ReadyToShoot = true;
}

void ARangeWeapon::GetAmmo(int32 count)
{
	int32 temp = count;
	temp -= CurrentAmmoInMagazine;
	
	if(temp < 0)
	{
		CurrentAmmoInMagazine = -temp;
	}
	else if(temp == 0)
	{
		CurrentAmmoInMagazine = 0;
	}
	else
	{
		CurrentAmmoInMagazine = 0;
		CurrentAdditionalAmmo -= temp;
	}

	if(CurrentAdditionalAmmo < 0)
	{
		CurrentAdditionalAmmo = 0;
	}
	
	if(OnChangeAmmoInMagazine.IsBound())
	{
		OnChangeAmmoInMagazine.Broadcast(CurrentAmmoInMagazine);
	}
	if(OnChangeAmmoInAdditionalAmmo.IsBound())
	{
		OnChangeAmmoInAdditionalAmmo.Broadcast(CurrentAdditionalAmmo);
	}
}

void ARangeWeapon::AddAmmo(int32 count)
{
	if (count <= 0)
		return;

	CurrentAdditionalAmmo += count;
	CurrentAdditionalAmmo = FMath::Clamp(CurrentAdditionalAmmo, 0, MaxAdditionalAmmo);
	if(OnChangeAmmoInAdditionalAmmo.IsBound())
	{
		OnChangeAmmoInAdditionalAmmo.Broadcast(CurrentAdditionalAmmo);
	}
}
