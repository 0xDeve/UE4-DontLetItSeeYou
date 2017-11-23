// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupBattery.h"


// Sets default values
APickupBattery::APickupBattery()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create a static mesh component
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Battery"));
	// All batteries start active
	bIsActive = true;
	// Set root component for the battery
	RootComponent = PickupMesh;
}

// Called when the game starts or when spawned
void APickupBattery::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupBattery::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APickupBattery::IsActive()
{
	return bIsActive;
}

void APickupBattery::SetActive(bool PickupState)
{
	bIsActive = PickupState;
}

void APickupBattery::WasCollected_Implementation()
{
	FString PickupDebugString = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *PickupDebugString);
}

