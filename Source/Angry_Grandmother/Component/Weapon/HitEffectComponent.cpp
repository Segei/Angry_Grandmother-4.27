// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Weapon/HitEffectComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UHitEffectComponent::InjectToBarrel(UWeaponBarrelComponent* Barrel)
{
	Barrel->OnHitToDamageInterface.AddDynamic(this, &UHitEffectComponent::PlayEffectDamageInterface);
	Barrel->OnHitToOtherActor.AddDynamic(this, &UHitEffectComponent::PlayEffectOtherActor);
}

void UHitEffectComponent::PlayEffectDamageInterface(FHitResult Result)
{
	if(!IsValid(DamageInterfaceEffect))
	{
		return;
	}
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DamageInterfaceEffect, Result.Location, Result.ImpactNormal.Rotation());
}

void UHitEffectComponent::PlayEffectOtherActor(FHitResult Result)
{
}


