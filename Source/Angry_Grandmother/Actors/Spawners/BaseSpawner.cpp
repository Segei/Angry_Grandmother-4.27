// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Spawners/BaseSpawner.h"
#include "SpawnPoint.h"

// Sets default values
ABaseSpawner::ABaseSpawner()
{
}

void ABaseSpawner::BeginPlay()
{
	Super::BeginPlay();
	TrySpawnObject();
	if(bNeedSpawnObjectByTimer)
	{
		StartSpawnNext();
	}
}

void ABaseSpawner::TrySpawnObject()
{
	TArray<ASpawnPoint*> tempArray = SpawnPoints;
	ASpawnPoint* Point = nullptr;
	while (tempArray.Num() > 0)
	{
		Point = tempArray[FMath::RandRange(0,tempArray.Num()-1)];
		tempArray.Remove(Point);
		if (Point)
		{
			if (Point->CheckPosition())
			{
				break;
			}
			Point = nullptr;
		}
	}
	if(Point)
	{
		SpawnObject(Point);
	}
	if(bNeedSpawnObjectByTimer)
	{
		StartSpawnNext();
	}
}

AActor* ABaseSpawner::SpawnObject(AActor* Point)
{
	return GetWorld()->SpawnActor<AActor>(SpawnedObject, Point->GetActorLocation(), Point->GetActorRotation());
}

void ABaseSpawner::StartSpawnNext()
{
	GetWorldTimerManager().SetTimer(TimeSpawnNext, this, &ABaseSpawner::TrySpawnObject, TimeSpawn);
}
