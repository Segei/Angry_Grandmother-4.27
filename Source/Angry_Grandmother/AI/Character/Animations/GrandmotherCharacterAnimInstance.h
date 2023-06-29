// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "GrandmotherCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ANGRY_GRANDMOTHER_API UGrandmotherCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed;

	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	TWeakObjectPtr<class ABaseCharacter> CacheCharacter; 
};
