// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

 #include "CoreMinimal.h"
#include "WeaponBarrelComponent.h"
#include "Components/ActorComponent.h"
#include "NiagaraComponent.h"
#include "HitEffectComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANGRY_GRANDMOTHER_API UHitEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void InjectToBarrel(UWeaponBarrelComponent* Barrel);
	UFUNCTION()
	void PlayEffectDamageInterface(FHitResult Result);
	UFUNCTION()
	void PlayEffectOtherActor(FHitResult Result);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UNiagaraSystem* DamageInterfaceEffect;
};
