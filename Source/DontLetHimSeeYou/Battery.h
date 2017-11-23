// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupBattery.h"
#include "Battery.generated.h"

/**
 * 
 */
UCLASS()
class DONTLETHIMSEEYOU_API ABattery : public APickupBattery
{
	GENERATED_BODY()
	
public:
	ABattery();
	
	/** Override the WasCollected function - use Implementation because it is a bp Navtive event*/
	void WasCollected_Implementation() override;
};
