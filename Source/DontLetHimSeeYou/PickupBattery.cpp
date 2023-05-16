// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupBattery.h"
#include "DontLetHimSeeYouCharacter.h"

// Sets default values
APickupBattery::APickupBattery()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create a static mesh component
	// All batteries start active
	bIsActive = true;
}

// Called when the game starts or when spawned
void APickupBattery::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->SetSimulatePhysics(true);
}

// Called every frame
void APickupBattery::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupBattery::OnPickup_Implementation(class ADontLetHimSeeYouCharacter* InInteractor)
{
	if (InInteractor) {
		InInteractor->IncreaseBattery(20);
		InInteractor->RemoveItemFromInventory(this);
		Destroy();
	}
	Super::OnPickup_Implementation(InInteractor);
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

