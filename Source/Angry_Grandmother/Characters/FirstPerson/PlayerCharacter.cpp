// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/FirstPerson/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Component/Character/ScoreComponent.h"

APlayerCharacter::APlayerCharacter()
{
	Camera = CreateDefaultSubobject<UCameraComponent>("FirstPersonCamera");
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;
	Camera->SetRelativeLocationAndRotation(FVector(-10.000000,0.000000,60.000000), FRotator::ZeroRotator);
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("FirstPersonMesh");
	MeshComponent->SetupAttachment(Camera);
	MeshComponent->SetRelativeLocationAndRotation(FVector(-30.000000,0.000000,-151.327179), FRotator::ZeroRotator);
	
	Score = CreateDefaultSubobject<UScoreComponent>("ScoreComponent");
}

void APlayerCharacter::TakeHealing(float Heal)
{
	IHealingInterface::TakeHealing(Heal);
	Health->TakeHeal(Heal);
}

void APlayerCharacter::SetWeapon(ARangeWeapon* Weapon)
{
	CurrentWeapon = Weapon;
	if (OnSetWeapon.IsBound())
	{
		OnSetWeapon.Broadcast(this);
	}
}
