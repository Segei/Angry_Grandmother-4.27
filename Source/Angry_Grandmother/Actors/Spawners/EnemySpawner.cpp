// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Spawners/EnemySpawner.h"

#include "AI/Character/EnemyCharacter.h"
#include "AI/Controllers/AICharacterController.h"

void AEnemySpawner::BeginPlay()
{
	bNeedSpawnObjectByTimer = false;
	CachePlayer = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Super::BeginPlay();
}

AActor* AEnemySpawner::SpawnObject(AActor* Point)
{
	AActor* Object = Super::SpawnObject(Point);
	if(!Object)
	{
		return Object;
	}
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(Object);
	EnemyCharacter->OnCharacterDeath.AddDynamic(this, &AEnemySpawner::EnemyDeathSpawnNew);
	AAICharacterController* Enemy =Cast<AAICharacterController>(EnemyCharacter->Controller);
	if(Enemy)
	{
		Enemy->SetTargetReference(CachePlayer);
	}
	return  Object;
}

void AEnemySpawner::EnemyDeathSpawnNew(ABaseCharacter* Character)
{
	Character->OnCharacterDeath.RemoveDynamic(this, &AEnemySpawner::EnemyDeathSpawnNew);
	int32 CountNewEnemy = FMath::RandRange(MinCountRespawnNewEnemy, MaxCountRespawnNewEnemy);
	for (int32 i = 0; i < CountNewEnemy; i++)
 	{
 		TrySpawnObject();
 	}
}


