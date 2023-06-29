// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/AngryGrandmotherController.h"
#include "GameFramework/GameModeBase.h"

void AAngryGrandmotherController::SetPawn(APawn* InPawn)
{
	if (APlayerCharacter* OldPlayerCharacter = Cast<APlayerCharacter>(GetPawn()))
	{
		OldPlayerCharacter->OnCharacterDeath.RemoveDynamic(this, &AAngryGrandmotherController::PlayerDeath);
	}

	Super::SetPawn(InPawn);
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(InPawn);
	if (IsValid(PlayerCharacter) && GetLocalRole() == ENetRole::ROLE_Authority)
	{
		PlayerCharacter->OnCharacterDeath.AddDynamic(this, &AAngryGrandmotherController::PlayerDeath);
	}

	if (OnSpawnPlayer.IsBound())
	{
		OnSpawnPlayer.Broadcast();
	}
	CurrentLife = MaxLife;
}

void AAngryGrandmotherController::PlayerDeath(ABaseCharacter* DeathCharacter)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(DeathCharacter);
	if (!IsValid(PlayerCharacter) || CurrentLife <= 0)
	{
		return;
	}
	int32 spawnPoint = FMath::RandRange(1, 4);
	AActor* playerStart = GetWorld()->GetAuthGameMode()->FindPlayerStart(this, FString::FromInt(spawnPoint));
	PlayerCharacter->SetActorLocation(playerStart->GetActorLocation());
	PlayerCharacter->SetActorRotation(playerStart->GetActorRotation());
	PlayerCharacter->TakeHealing(60.f);
	if (IsValid(PlayerCharacter->CurrentWeapon))
	{
		PlayerCharacter->CurrentWeapon->GetAmmo(60);
	}

	CurrentLife--;
	if (OnChangeLifeCount.IsBound())
	{
		OnChangeLifeCount.Broadcast(CurrentLife);
	}
	if (CurrentLife <= 0)
	{
		if (OnEndLife.IsBound())
			OnEndLife.Broadcast();
	}
}
