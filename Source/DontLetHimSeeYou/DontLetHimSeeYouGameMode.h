// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "DontLetHimSeeYouGameMode.generated.h"


UCLASS(minimalapi)
class ADontLetHimSeeYouGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	ADontLetHimSeeYouGameMode();
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, Category = "Spawn points")
		TSubclassOf <class ASpawnPoints> SpawnPoints_C;
	UPROPERTY(EditDefaultsOnly, Category = "Spawn points")
		TSubclassOf<class APedo> PedoToSpawn_C;
private:
	TArray<AActor*> SpawnPoints;
	int32 maxPedos = 2;
	int32 currentPedos;
	void SpawnPedos(int32 Index);
};



