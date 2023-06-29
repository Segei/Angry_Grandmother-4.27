// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include  "Components/SphereComponent.h"
#include "PickupHeal.generated.h"

UCLASS()
class ANGRY_GRANDMOTHER_API APickupHeal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupHeal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MinHealth = 20.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth = 40.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* SoundPickup;
public:
	UFUNCTION()
	void Pickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
