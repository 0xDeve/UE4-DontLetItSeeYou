// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnVolume.h"
#include "Kismet/KismetMathLibrary.h"
#include "PickupBattery.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Create the box component to represent the spawn volume
	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn volume"));
	RootComponent = WhereToSpawn;
	
	SpawnDelayLow = 5.f;
	SpawnDelayHigh = 25.f;
	SpawnSkillMin = 60.f;
	SpawnSkillMax = 120.f;
}

FVector ASpawnVolume::GetRandomPointsInVolume()
{
	FVector SpawnOrigin = WhereToSpawn->Bounds.Origin;
	FVector SpawnExtent = WhereToSpawn->Bounds.BoxExtent;
	// Return random point within the box
	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	SpawnDelay = FMath::FRandRange(SpawnDelayLow, SpawnDelayHigh);
	SpawnSkillDelay = FMath::FRandRange(SpawnSkillMin, SpawnSkillMax);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnSkill, SpawnSkillDelay, false);
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnVolume::SpawnPickup()
{
	// Check if WhatToSpawn has been set
	if (WhatToSpawn != NULL) {
		// Check for a valid world
		UWorld* const World = GetWorld();
		if (World) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			// Get a random location 
			FVector RandomLocation = GetRandomPointsInVolume();
			
			// Get a random rotation for the spawned item
			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.0f;
			SpawnRotation.Pitch = FMath::FRand() * 360.0f;
			SpawnRotation.Roll = FMath::FRand() * 360.0f;
			// Spawn the item
			APickupBattery* const SpawnedItem = World->SpawnActor<APickupBattery>(WhatToSpawn, RandomLocation, SpawnRotation, SpawnParams);

			SpawnDelay = FMath::FRandRange(SpawnDelayLow, SpawnDelayHigh);
			GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnPickup, SpawnDelay, false);
		}
	}
}

void ASpawnVolume::SpawnSkill()
{
	for (int32 i = 0; i < SkillToSpawn.Num(); i++) {
		if (SkillToSpawn[i] == NULL) return;
	}
	UWorld* const World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;

		// Get a random location 
		FVector RandomLocation = GetRandomPointsInVolume();

		// Get a random rotation for the spawned item
		FRotator SpawnRotation;
		SpawnRotation.Yaw = FMath::FRand() * 360.0f;
		SpawnRotation.Pitch = FMath::FRand() * 360.0f;
		SpawnRotation.Roll = FMath::FRand() * 360.0f;
		// Spawn the item
		int32 RandomItemIndex = FMath::RandRange(0, SkillToSpawn.Num()-1);
		World->SpawnActor<AActor>(SkillToSpawn[RandomItemIndex], RandomLocation, SpawnRotation, SpawnParams);
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *SkillToSpawn[RandomItemIndex]->GetName());
		SpawnDelay = FMath::FRandRange(SpawnSkillMin, SpawnSkillMax);
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnVolume::SpawnSkill, SpawnSkillDelay, false);
	}
}