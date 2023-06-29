// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

UCLASS()
class ANGRY_GRANDMOTHER_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Radius = 15.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<AActor*> IgnoredActors;
	ASpawnPoint();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CheckPosition() const;
};
