// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Weapon/WeaponBarrelComponent.h"

#include "Interfaces/DamageInterface.h"
#include "Component/CustomDamageZone.h"
#include "Kismet/GameplayStatics.h"


UWeaponBarrelComponent::UWeaponBarrelComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UWeaponBarrelComponent::Shoot(float WeaponDamage)
{
	FHitResult ShootResult;
	FCollisionQueryParams param = FCollisionQueryParams{};
	param.AddIgnoredActor(GetOwner()->GetOwner());
	FVector StartPosition, EndPosition;
	APlayerCameraManager* cameraPosition = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

	StartPosition = cameraPosition->GetCameraLocation();

	EndPosition = StartPosition + cameraPosition->GetActorForwardVector() * LenghtShoot;

	bool bHasHit = GetWorld()->LineTraceSingleByChannel(ShootResult, StartPosition, EndPosition,
	                                                    UEngineTypes::ConvertToCollisionChannel(
		                                                    UEngineTypes::ConvertToTraceType(ECC_Visibility)),
	                                                    param);

	if (!bHasHit)
	{
		return;
	}

	float mulScore = 1.f;
	float mulDamage = 1.f;
	if (UCustomDamageZone* hitZone = Cast<UCustomDamageZone>(ShootResult.Component))
	{
		mulDamage = hitZone->DamageMultiply;
		mulScore = hitZone->ScoreMultiply;
	}

	if (IDamageInterface* result = Cast<IDamageInterface>(ShootResult.GetActor()))
	{
		result->TakeDamage(WeaponDamage * mulDamage);
		if (GetScoreMultiply.IsBound())
		{
			GetScoreMultiply.Broadcast(mulScore);
		}
		if(OnHitToDamageInterface.IsBound())
		{
			OnHitToDamageInterface.Broadcast(ShootResult);
		}
	}
	else
	{
		if(OnHitToOtherActor.IsBound())
		{
			OnHitToOtherActor.Broadcast(ShootResult);
		}
	}
}
