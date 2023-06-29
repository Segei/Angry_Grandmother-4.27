// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeHealth, float, ValueHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEmptyHealth);
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ANGRY_GRANDMOTHER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FChangeHealth ChangeCurrentHealth;
	UPROPERTY(BlueprintAssignable)
	FOnEmptyHealth OnEmptyHealth;
	UHealthComponent();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth = 100.f;

public:	
	virtual void TakeDamage(float Damage);
	virtual void TakeHeal(float Heal);
};
