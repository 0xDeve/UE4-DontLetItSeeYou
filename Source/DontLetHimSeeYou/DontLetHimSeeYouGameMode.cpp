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
}

void ADontLetHimSeeYouGameMode::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsWithTag(this, TEXT("Monster Spawn"), SpawnPoints);
	SpawnMonsters();

	GetWorldTimerManager().SetTimer(SpawnHandle, this, &ADontLetHimSeeYouGameMode::SpawnMonsters, SpawnRate, true);
}

void ADontLetHimSeeYouGameMode::SpawnMonsters()
{
	if (CurrentMonsters < MaxMonsters) {
		int32 RandomIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<APedo>(PedoToSpawn_C, SpawnPoints[RandomIndex]->GetActorLocation(), SpawnPoints[RandomIndex]->GetActorRotation(), SpawnInfo);
		CurrentMonsters++;
	}
}