// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Character/Animations/GrandmotherCharacterAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"

void UGrandmotherCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	checkf(
	TryGetPawnOwner()->IsA<ABaseCharacter>(),
	TEXT("UGrandmotherCharacterAnimInstance::NativeBeginPlay() UGrandmotherCharacterAnimInstance can be used only with ABaseCharacter")
	);
	CacheCharacter = StaticCast<ABaseCharacter*>(TryGetPawnOwner());	
}

void UGrandmotherCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(!CacheCharacter.IsValid())
	{
		return;
	}
	Speed = CacheCharacter->GetCharacterMovement()->Velocity.Size();
}
