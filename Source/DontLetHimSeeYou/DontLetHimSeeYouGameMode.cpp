// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DontLetHimSeeYouGameMode.h"
#include "DontLetHimSeeYouCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Pedo.h"
#include "SpawnPoints.h"
#include "UObject/ConstructorHelpers.h"

ADontLetHimSeeYouGameMode::ADontLetHimSeeYouGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/RunnerBP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ADontLetHimSeeYouGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (currentPedos < 2) {
		for (int32 i = currentPedos; i < maxPedos; i++)
			SpawnPedos(i);
	}
		// TODO Spawn pedo to match
}

void ADontLetHimSeeYouGameMode::BeginPlay()
{
	Super::BeginPlay();
	for (int32 i = currentPedos; i < maxPedos; i++)
		SpawnPedos(i);
}

void ADontLetHimSeeYouGameMode::SpawnPedos(int32 Index)
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), SpawnPoints_C, SpawnPoints);
	FVector SpawnPointLocation;
	FRotator SpawnPointRotation;
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnPointLocation = SpawnPoints[Index]->GetActorLocation();
	SpawnPointRotation = SpawnPoints[Index]->GetActorRotation();
	GetWorld()->SpawnActor<APedo>(PedoToSpawn_C, SpawnPointLocation, SpawnPointRotation, SpawnInfo);
	currentPedos++;
}