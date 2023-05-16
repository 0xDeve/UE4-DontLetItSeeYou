// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DontLetHimSeeYouCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Pedo_Grabber.h"
#include "RunnerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "PickupBattery.h"
#include "PickupActor.h"

//////////////////////////////////////////////////////////////////////////
// ADontLetHimSeeYouCharacter

ADontLetHimSeeYouCharacter::ADontLetHimSeeYouCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 800.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a first person camera component
	FP_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("First person camera"));
	FP_Camera->SetupAttachment(GetMesh(), TEXT("FP_Camera"));
	FP_Camera->SetRelativeLocation(FVector(0.f, 20.f, 0.f));
	FP_Camera->SetRelativeRotation(FRotator(- 90.f, 0.f, 90.f));
	FP_Camera->bUsePawnControlRotation = true;
	// Create a flash light component
	Flashlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flash light"));
	//Flashlight->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("flash"));
	Flashlight->SetupAttachment(FP_Camera, TEXT(""));
	Flashlight->Intensity = 10000.f;
	Flashlight->InnerConeAngle = 9.f;
	Flashlight->OuterConeAngle = 12.3f;
	Flashlight->SourceLength = 1.f;
	Flashlight->SetVisibility(false);
	//
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	// Create audio component
	BreathSound = CreateDefaultSubobject<UAudioComponent>(TEXT("Breathing sound"));
	BreathSound->SetupAttachment(GetMesh(), TEXT("Breathing sound"));
	BreathSound->bAutoActivate = false;
	RecoverySound = CreateDefaultSubobject<UAudioComponent>(TEXT("Recovery sound"));
	RecoverySound->SetupAttachment(GetMesh(), TEXT("Recovery sound"));
	RecoverySound->bAutoActivate = false;
}

//////////////////////////////////////////////////////////////////////////
// Input
void ADontLetHimSeeYouCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Battery decrease ||  TODO Fix bug
	if (bisOn == true && Battery>0) { // If flashlight is on and battery > 0 then decrease battery 
		Battery = Battery - DeltaTime * 1.5;
	}
	if (Battery <= 9 && bisOn == true) { // If battery < 9 and flashlight is on then turn it off
		bisOn = false;
		Flashlight->ToggleVisibility();
		Battery = 0; // Adjustment to stamina not matching the HUD
	}
	///
	// Stamina decrease || TODO Fix bug
	if (bisSprint == true && Stamina > 0) { // If is sprinting and still has stamina then decrease stamina by time
		Stamina -= DeltaTime * 7;
		if (Stamina <= 50 && bPlayBreath == false) { // If stamina less than 50 and breathsound isnt played then play it and stop the recovery sound also
			BreathSound->Play(); 
			RecoverySound->Stop();
			bPlayHeal = false;
			bPlayBreath = true;
		}
	}
	else if (bisSprint == true && Stamina <= 9) { // If is sprinting and stamina is less than runable limit then stop sprinting
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
		bisSprint = false;
		if (bPlayBreath == true && bPlayHeal == false) { // If is playing breathsound then stop 
			BreathSound->Stop();
			bPlayBreath = false;
		}
	}
	else if (bisSprint == false) { // If not sprinting then increase stamina by time 
		Stamina += DeltaTime * 5;
		if (Stamina <= 50 && Stamina > 0 && bPlayHeal == false) { // If stamina < 50 and > 0 then play recovery sound and stop breathsound
			RecoverySound->Play();
			BreathSound->Stop();
			bPlayBreath = false;
			bPlayHeal = true;
		}
		else if (Stamina > 50 && bPlayHeal == true) { // If stamina > 50 then stop recovery sound
			RecoverySound->Stop();
			bPlayHeal = false;
		}
		else if (Stamina > 100){ // If stamina exceeds 100 then set it to 100
			Stamina = 100;
		}
	}
	else {
		Stamina += DeltaTime * 5; // Increase stamina by delta time mutiplication
		if (Stamina > 100)
			Stamina = 100;
	}
	///
	
}

void ADontLetHimSeeYouCharacter::AddItemToInventory(APickupActor* InPickupActor)
{
	if (CurrentSkills > MaxSkills) {
		return;
	}
	PickedUpActors.Add(InPickupActor);
	CurrentSkills++;
}

void ADontLetHimSeeYouCharacter::RemoveItemFromInventory(APickupActor* InItem)
{
	if (PickedUpActors.Find(InItem)) {
		PickedUpActors.Remove(InItem);
	}
}

void ADontLetHimSeeYouCharacter::IncreaseBattery(float BatteryEnergy)
{
	if (Battery < 100 && Battery >= 80) {
		Battery = 100;
	}
	else Battery += BatteryEnergy;
}

bool ADontLetHimSeeYouCharacter::get_bIsSprint()
{
	return bisSprint;
}

void ADontLetHimSeeYouCharacter::set_bIsSprint(bool ValueToSet) {
	bisSprint = ValueToSet;
}

void ADontLetHimSeeYouCharacter::set_bIsOn() {
	bisOn = !bisOn;
}