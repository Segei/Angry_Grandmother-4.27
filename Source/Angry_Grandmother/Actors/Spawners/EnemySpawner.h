// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Spawners/BaseSpawner.h"
#include "Characters/FirstPerson/PlayerCharacter.h"
#include "EnemySpawner.generated.h"

/**
 * 
 */
UCLASS()
class ANGRY_GRANDMOTHER_API AEnemySpawner : public ABaseSpawner
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual AActor* SpawnObject(AActor* Point) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	APlayerCharacter* CachePlayer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxCountRespawnNewEnemy = 2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MinCountRespawnNewEnemy = 1;

	UFUNCTION(BlueprintCallable)
	void EnemyDeathSpawnNew(ABaseCharacter* Character);
};
