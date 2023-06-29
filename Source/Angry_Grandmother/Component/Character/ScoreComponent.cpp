// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Character/ScoreComponent.h"
#include "SaveScore.h"
#include "Characters/FirstPerson/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UScoreComponent::UScoreComponent()
{
}

void UScoreComponent::LinkScoreComponentToWeapon(APlayerCharacter* Player)
{
	Player->CurrentWeapon->BarrelComponent->GetScoreMultiply.AddDynamic(this, &UScoreComponent::AddScore);
}

void UScoreComponent::BeginPlay()
{
	Super::BeginPlay();
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwner());
	Player->OnSetWeapon.AddDynamic(this, &UScoreComponent::LinkScoreComponentToWeapon);
	if (USaveScore* LoadedGame = Cast<USaveScore>(UGameplayStatics::LoadGameFromSlot(SlotName, 0)))
	{
		// The operation was successful, so LoadedGame now contains the data we saved earlier.
		UE_LOG(LogTemp, Warning, TEXT("LOADED: %f"), LoadedGame->Score);
		BestScore = LoadedGame->Score;
		if (OnLoadBestScore.IsBound())
		{
			OnLoadBestScore.Broadcast(BestScore);
		}
	}
}

void UScoreComponent::BeginDestroy()
{
	Super::BeginDestroy();
	UE_LOG(LogTemp, Warning, TEXT("End Score: %f"), CurrentScore);
	if (BestScore >= CurrentScore)
	{
		return;
	}
	
	
	if (USaveScore* SaveGameInstance = Cast<USaveScore>(
		UGameplayStatics::CreateSaveGameObject(
				type
			)))
	{
		SaveGameInstance->Score = CurrentScore;
		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0))
		{
			UE_LOG(LogTemp, Warning, TEXT("Save score"));
		}
	}
}

void UScoreComponent::AddScore(float Multiply)
{
	CurrentScore += BaseScoreForShoot * Multiply;
	if (OnChangeScore.IsBound())
	{
		OnChangeScore.Broadcast(CurrentScore);
	}
	UE_LOG(LogTemp, Warning, TEXT("Current Score: %f"), CurrentScore);
}
