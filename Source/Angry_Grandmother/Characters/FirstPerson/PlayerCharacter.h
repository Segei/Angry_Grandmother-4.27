// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapons/RangeWeapon.h"
#include "Characters/BaseCharacter.h"
#include "Component/Character/ScoreComponent.h"
#include "Interfaces/HealingInterface.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;

UCLASS()
class ANGRY_GRANDMOTHER_API APlayerCharacter : public ABaseCharacter, public  IHealingInterface
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeWeapon, APlayerCharacter*, Player);
	GENERATED_BODY()
public:
	APlayerCharacter();
	virtual  void TakeHealing(float Heal) override;
	UFUNCTION(BlueprintCallable)
	void SetWeapon(ARangeWeapon* Weapon);
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ARangeWeapon* CurrentWeapon;
	UPROPERTY(BlueprintAssignable)
	FChangeWeapon OnSetWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UScoreComponent* Score;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* MeshComponent;

};
