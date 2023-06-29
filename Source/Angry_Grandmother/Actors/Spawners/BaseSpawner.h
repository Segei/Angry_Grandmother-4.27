// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSpawner.generated.h"

class ASpawnPoint;
UCLASS()
class ANGRY_GRANDMOTHER_API ABaseSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSpawner();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<ASpawnPoint*> SpawnPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> SpawnedObject;


protected:
	virtual void BeginPlay() override;
	void TrySpawnObject();
	virtual AActor* SpawnObject(AActor* Point);
	void StartSpawnNext();
	UPROPERTY()
	bool bNeedSpawnObjectByTimer = true;
	UPROPERTY()
	FTimerHandle TimeSpawnNext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TimeSpawn = 5.f;
};