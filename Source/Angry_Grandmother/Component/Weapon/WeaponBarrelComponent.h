// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WeaponBarrelComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreMultiply, float, Multiply);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FShootHit, FHitResult, Result);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ANGRY_GRANDMOTHER_API UWeaponBarrelComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UWeaponBarrelComponent();
	void Shoot(float WeaponDamage);
	UPROPERTY(BlueprintAssignable)
	FScoreMultiply GetScoreMultiply;
	UPROPERTY(BlueprintAssignable)
	FShootHit OnHitToOtherActor;
	UPROPERTY(BlueprintAssignable)
	FShootHit OnHitToDamageInterface;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float LenghtShoot = 4000.f;
};
