// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class DONTLETHIMSEEYOU_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();
	// Spawn volume
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawning")
		class UBoxComponent* WhereToSpawn;
	FORCEINLINE class UBoxComponent* GetWhereToSpawn() const { return WhereToSpawn; }
	UFUNCTION(BlueprintPure, Category = "Spawning")
		FVector GetRandomPointsInVolume();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/** The pickup to spawn */
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class APickupBattery> WhatToSpawn;
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TArray<TSubclassOf<class AActor>> SkillToSpawn;
	FTimerHandle SpawnTimer;

	/** Minimum spawn delay */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning")
		float SpawnDelayLow;
	/** Maximum spawn delay */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning")
		float SpawnDelayHigh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		float SpawnSkillMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		float SpawnSkillMax;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	
	void SpawnPickup();
	void SpawnSkill();
	float SpawnDelay;
	float SpawnSkillDelay;
};
