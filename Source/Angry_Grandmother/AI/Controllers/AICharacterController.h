// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Characters/BaseCharacter.h"
#include "AICharacterController.generated.h"

/**
 * 
 */
UCLASS()
class ANGRY_GRANDMOTHER_API AAICharacterController : public AAIController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName NamePropertyPlayerInBlackBoard = "PlayerCharacter";
	void SetTargetReference(ABaseCharacter* Player);
	virtual void SetPawn(APawn* InPawn) override;
	
};
