// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Weapon/HitEffectComponent.h"
#include "Component/Weapon/WeaponBarrelComponent.h"
#include "GameFramework/Actor.h"
#include "RangeWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeAmmo, int32, Ammo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShoting);
UCLASS()
class ANGRY_GRANDMOTHER_API ARangeWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ARangeWeapon();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Ammo settings | Current")
	int32 CurrentAmmoInMagazine = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Ammo settings | Current")
	int32 CurrentAdditionalAmmo = 60;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool ReadyToShoot;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void StartReload();
	UFUNCTION(BlueprintCallable)
	void EndReload();
	UFUNCTION(BlueprintCallable)
	void StartShooting();
	UFUNCTION(BlueprintCallable)
	void EndShooting();
	void TryShoot();
	void EndShoot();
	void GetAmmo(int32 count);
	UFUNCTION(BlueprintCallable)
	void AddAmmo(int32 count);
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWeaponBarrelComponent* BarrelComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UHitEffectComponent* HitEffectComponent;
	UPROPERTY(BlueprintAssignable)
	FChangeAmmo OnChangeAmmoInMagazine;
	UPROPERTY(BlueprintAssignable)
	FChangeAmmo OnChangeAmmoInAdditionalAmmo;
	UPROPERTY(BlueprintAssignable)
	FShoting OnShootRifle;

protected:
	USceneComponent* Root;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* MeshWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimationAsset* AnimationReloadNoEmpty;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimationAsset* AnimationReloadEmpty;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimationAsset* AnimationShoot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* NoAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage = 20;
	UPROPERTY()
	FTimerHandle ShootDelay;
	
	// Called when the game starts or when spawned
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo settings | Limites")
	int32 MaxAmmoInMagazine = 30;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo settings | Limites")
	int32 MaxAdditionalAmmo = 270;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun Settings")
	float RPM = 360.f;
	UPROPERTY()
	float DelayBetweenShoot;
	virtual void BeginPlay() override;

	

private:
	bool Shooting;
	bool CanReload;
	bool CanShooting;
};
