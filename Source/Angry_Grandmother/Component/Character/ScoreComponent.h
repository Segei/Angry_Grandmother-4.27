// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreComponent.generated.h"

class USaveScore;
class APlayerCharacter;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScoreNotify, float, Score);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ANGRY_GRANDMOTHER_API UScoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UScoreComponent();
	UPROPERTY(BlueprintAssignable)
	FScoreNotify OnChangeScore;
	UPROPERTY(BlueprintAssignable)
	FScoreNotify OnLoadBestScore;

	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	float BestScore = 0.f;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin = 0.1f, ClampMax = 9999))
	float BaseScoreForShoot = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<USaveScore> type;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString SlotName = "Score";
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	UFUNCTION()
	void LinkScoreComponentToWeapon(APlayerCharacter* Player);
	UFUNCTION()
	void AddScore(float Multiply);

private:
	
	float CurrentScore = 0.f;
};
