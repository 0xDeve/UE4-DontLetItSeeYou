// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "DontLetHimSeeYouCharacter.h"
#include "RunnerController.generated.h"

/**
 * 
 */
UCLASS()
class DONTLETHIMSEEYOU_API ARunnerController : public APlayerController
{
	GENERATED_BODY()
public:
	/** Flashlight toggle sound effect */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
		class USoundBase* FlashLightToggleVFX;
private:
	virtual void SetupInputComponent() override;

	APawn* ControlledPawn;

	/** Toggle flashlight*/
	void ToggleFlashLight();
	/** Called for forwards/backward input */
	void MoveForward(float Value);
	/** Called for side to side input */
	void MoveRight(float Value);
	/** Sprint */
	void Sprint();
	/** Stop sprinting*/
	void StopSprint();
};
