// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "CustomDamageZone.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ANGRY_GRANDMOTHER_API UCustomDamageZone : public UCapsuleComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageMultiply = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ScoreMultiply = 1.f;
};
