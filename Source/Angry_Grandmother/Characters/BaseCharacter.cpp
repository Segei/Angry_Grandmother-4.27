// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseCharacter::ABaseCharacter()
{
	Health = CreateDefaultSubobject<UHealthComponent>("Health");
}

void ABaseCharacter::TakeDamage(float Damage)
{
	IDamageInterface::TakeDamage(Damage);
	Health->TakeDamage(Damage);
}

void ABaseCharacter::CharacterDead()
{	
	if(IsValid(CharacterDeadMontage))
	{
		GetMesh()->GetAnimInstance()->Montage_Play(CharacterDeadMontage);
	}
	OnCharacterDeath.Broadcast(this);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	Health->OnEmptyHealth.AddDynamic(this, &ABaseCharacter::CharacterDead);
}
