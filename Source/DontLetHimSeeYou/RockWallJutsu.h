// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupActor.h"
#include "RockWallJutsu.generated.h"

UCLASS()
class DONTLETHIMSEEYOU_API ARockWallJutsu : public APickupActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARockWallJutsu();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
