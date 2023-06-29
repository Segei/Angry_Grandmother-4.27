// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/FirstPerson/PlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "AngryGrandmotherController.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FControllerEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLife, int32, CountLife);

/**
 * 
 */
UCLASS()
class ANGRY_GRANDMOTHER_API AAngryGrandmotherController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FControllerEvent OnSpawnPlayer;
	UPROPERTY(BlueprintAssignable)
	FLife OnChangeLifeCount;
	UPROPERTY(BlueprintAssignable)
	FControllerEvent OnEndLife;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 CurrentLife;
protected:
	virtual void SetPawn(APawn* InPawn) override;
	UFUNCTION()
	void PlayerDeath(ABaseCharacter* DeathCharacter);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxLife = 3;
};
