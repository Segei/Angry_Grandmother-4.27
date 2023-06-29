// Fill out your copyright notice in the Description page of Project Settings.
#include "AI/Character/EnemyCharacter.h"

#include "AI/Controllers/AICharacterController.h"
#include "Components/CapsuleComponent.h"

UBehaviorTree* AEnemyCharacter::GetBehaviorTree() const
{
	return BehaviorTree;
}


void AEnemyCharacter::CharacterDead()
{
	Super::CharacterDead();
	Health->OnEmptyHealth.RemoveDynamic(this, &AEnemyCharacter::CharacterDead);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AAICharacterController* AIController =Cast<AAICharacterController>(Controller);
	AIController->BrainComponent->StopLogic("Death");
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

