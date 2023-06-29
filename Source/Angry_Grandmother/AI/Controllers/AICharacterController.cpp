// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Controllers/AICharacterController.h"

#include "AI/Character/EnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void AAICharacterController::SetTargetReference(ABaseCharacter* Player)
{
	if(Blackboard)
	{
		Blackboard->SetValueAsObject(NamePropertyPlayerInBlackBoard, Player);
	}
}

void AAICharacterController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(InPawn);
	if(EnemyCharacter)
	{
		RunBehaviorTree(EnemyCharacter->GetBehaviorTree());
	}
}
