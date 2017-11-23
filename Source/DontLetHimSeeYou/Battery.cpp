// Fill out your copyright notice in the Description page of Project Settings.

#include "Battery.h"

// Constructor
ABattery::ABattery()
{
	GetMesh()->SetSimulatePhysics(true);
}

void ABattery::WasCollected_Implementation()
{
	// Use the base pickup behavior
	Super::WasCollected_Implementation();
	// Destroy the battery
	Destroy();
}
