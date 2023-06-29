// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Spawners/SpawnPoint.h"

#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	//DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 50, FColor::Red);
}

bool ASpawnPoint::CheckPosition_Implementation() const
{
	FHitResult result;
	bool check =  !UKismetSystemLibrary::SphereTraceSingle(GetWorld(), GetActorLocation(), GetActorLocation(), Radius,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),  false, IgnoredActors,
		EDrawDebugTrace::ForDuration, result, true, FColor::Red, FColor::Green, 0.f);
	return check;
}


