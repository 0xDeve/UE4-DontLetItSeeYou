// Fill out your copyright notice in the Description page of Project Settings.

#include "RunnerController.h"
#include "DontLetHimSeeYouCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SpotLightComponent.h"
#include "PickupBattery.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"

void ARunnerController::ToggleFlashLight()
{
	/* Get pawn and do a cast **/
	ControlledPawn = this->GetPawn();
	auto Runner = Cast<class ADontLetHimSeeYouCharacter>(ControlledPawn);
	/***/
	if (Runner) {
		auto BatteryEnergy = Runner->Battery;
		if (BatteryEnergy > 0) {
			UGameplayStatics::PlaySoundAtLocation(this, FlashLightToggleVFX, Runner->GetActorLocation()); // TODO fix
			Runner->Flashlight->ToggleVisibility();
			Runner->set_bIsOn();
		}
	}
	else return;
}
void ARunnerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAction("Flash", IE_Pressed, this , &ARunnerController::ToggleFlashLight); // Toggle flashlight event
	InputComponent->BindAxis("MoveForward", this, &ARunnerController::MoveForward); // Move forward event
	InputComponent->BindAxis("MoveRight", this, &ARunnerController::MoveRight); // Move right event
	InputComponent->BindAxis("Turn", this, &APlayerController::AddYawInput); // Look up/down event
	InputComponent->BindAxis("LookUp", this, &APlayerController::AddPitchInput); // Look left/right event
	InputComponent->BindAction("Sprint", IE_Pressed, this, &ARunnerController::Sprint); // Sprint event
	InputComponent->BindAction("Sprint", IE_Released, this, &ARunnerController::StopSprint); // Stop sprint event
}

void ARunnerController::MoveForward(float Value)
{
	/* Get pawn and do a cast **/
	ControlledPawn = this->GetPawn();
	auto Runner = Cast<class ADontLetHimSeeYouCharacter>(ControlledPawn);
	/***/
	if (Runner) {
		if (Value != 0.0f)
		{
			// find out which way is forward
			const FRotator Rotation = this->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			Runner->AddMovementInput(Direction, Value);
		}
	}
}

void ARunnerController::MoveRight(float Value)
{
	/* Get pawn and do a cast **/
	ControlledPawn = this->GetPawn();
	auto Runner = Cast<class ADontLetHimSeeYouCharacter>(ControlledPawn);
	/***/
	if (Runner) {
		if (Value != 0.0f) {
			const FRotator Rotation = this->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			Runner->AddMovementInput(Direction, Value);
		}
	}
	else return;
}

void ARunnerController::Sprint()
{
	/* Get pawn and do a cast **/
	ControlledPawn = this->GetPawn();
	auto Runner = Cast<class ADontLetHimSeeYouCharacter>(ControlledPawn);
	/***/
	if (Runner) {
		auto Stamina = Runner->Stamina;
		if (Stamina > 0) {
			Runner->GetCharacterMovement()->MaxWalkSpeed = 1000.f; // Set maximum move speed
			Runner->set_bIsSprint(true); 
		}
	}
	else return;
}

void ARunnerController::StopSprint()
{
	/* Get pawn and do a cast **/
	ControlledPawn = this->GetPawn();
	auto Runner = Cast<class ADontLetHimSeeYouCharacter>(ControlledPawn);
	/***/
	if (Runner) {
		auto Stamina = Runner->Stamina;
		Runner->GetCharacterMovement()->MaxWalkSpeed = 600.f; // Reset maximum move speed
		Runner->set_bIsSprint(false);
	}
	else return;
}
