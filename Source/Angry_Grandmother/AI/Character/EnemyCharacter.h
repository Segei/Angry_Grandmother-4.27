// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class ANGRY_GRANDMOTHER_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	UBehaviorTree* GetBehaviorTree() const;

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBehaviorTree* BehaviorTree;
	virtual void CharacterDead() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
