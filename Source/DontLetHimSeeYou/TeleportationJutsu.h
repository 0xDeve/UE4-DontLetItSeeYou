// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupActor.h"
#include "TeleportationJutsu.generated.h"

UCLASS()
class DONTLETHIMSEEYOU_API ATeleportationJutsu : public APickupActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleportationJutsu();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnPickup_Implementation(class ADontLetHimSeeYouCharacter* InInteractor) override;

	UPROPERTY(EditAnywhere, Category = "Teleport points")
		TSubclassOf<AActor> ClassToFind;

	UPROPERTY(BlueprintReadOnly, Category = "Teleport points")
		TArray<AActor*> TeleportPoints;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
