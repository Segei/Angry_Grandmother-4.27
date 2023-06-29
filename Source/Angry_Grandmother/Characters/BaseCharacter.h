// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Spawners/BaseSpawner.h"
#include "Interfaces/DamageInterface.h"
#include "Component/Character/HealthComponent.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"


UCLASS()
class ANGRY_GRANDMOTHER_API ABaseCharacter : public ACharacter, public IDamageInterface
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetStateCharacte, ABaseCharacter*, Character);
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* CharacterDeadMontage;
	UFUNCTION()
	virtual void CharacterDead();
	virtual void BeginPlay() override;
public:
	UPROPERTY(BlueprintAssignable)
	FSetStateCharacte OnCharacterDeath;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UHealthComponent* Health;
	UFUNCTION(BlueprintCallable)
	virtual void TakeDamage(float Damage) override;
	
};
