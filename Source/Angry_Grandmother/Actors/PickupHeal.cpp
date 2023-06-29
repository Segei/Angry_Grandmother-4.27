// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PickupHeal.h"

#include "Interfaces/HealingInterface.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickupHeal::APickupHeal()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere Component");
	RootComponent= SphereComponent;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APickupHeal::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APickupHeal::Pickup);
}

void APickupHeal::Pickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if(IHealingInterface* Healing = Cast<IHealingInterface>(OtherActor))
	{
		Healing->TakeHealing(FMath::RandRange(MinHealth, MaxHealth));
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundPickup, GetActorLocation(), GetActorRotation());
		Destroy();
		
	}
	
}



