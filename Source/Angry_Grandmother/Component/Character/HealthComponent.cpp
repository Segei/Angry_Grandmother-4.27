// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/Character/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	if(ChangeCurrentHealth.IsBound())
		ChangeCurrentHealth.Broadcast(CurrentHealth);
}

void UHealthComponent::TakeDamage(float Damage)
{
	if(Damage <= 0)
		return;

	CurrentHealth -= Damage;
	if(CurrentHealth <= 0)
	{
		CurrentHealth = 0;
		if(OnEmptyHealth.IsBound())
		{
			OnEmptyHealth.Broadcast();
		}
	}
	if(ChangeCurrentHealth.IsBound())
		ChangeCurrentHealth.Broadcast(CurrentHealth);
}

void UHealthComponent::TakeHeal(float Heal)
{
	if(Heal <= 0)
		return;

	CurrentHealth += Heal;
	if(CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
	if(ChangeCurrentHealth.IsBound())
		ChangeCurrentHealth.Broadcast(CurrentHealth);
}

