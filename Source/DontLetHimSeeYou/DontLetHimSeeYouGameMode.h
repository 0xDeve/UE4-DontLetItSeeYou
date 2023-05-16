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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int32 MaxMonsters = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		float SpawnRate = 10;

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	int32 CurrentMonsters;
private:
	UPROPERTY()
	TArray<AActor*> SpawnPoints;

	void SpawnMonsters();

	FTimerHandle SpawnHandle;
};



