// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DontLetHimSeeYouCharacter.generated.h"

UCLASS(config=Game)
class ADontLetHimSeeYouCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	ADontLetHimSeeYouCharacter();
	/*Components*/
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FP_Camera;
	/** Spotlight component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpotLightComponent* Flashlight;
	/** Breath sound effect */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		class UAudioComponent* BreathSound;
	/** Recovery sound effect */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		class UAudioComponent* RecoverySound;
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	/** Attributes */
	/** Flashlight battery */
	UPROPERTY(BlueprintReadOnly, Category = "Battery")
		float Battery = 40.f;
	/** Runner stamina */
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
		float Stamina = 100.f;
	/** Character name*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character")
		FText CharacterName;
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attributes")
		int32 MaxSkills = 3;

	UPROPERTY(BlueprintReadWrite, Category = "Attributes")
	int32 CurrentSkills;

	UPROPERTY(BlueprintReadOnly)
	TArray<class APickupActor*> PickedUpActors;

	/** Increase battery energy */
	void IncreaseBattery(float BatteryEnergy);
	/** Getter bisSprint */
	bool get_bIsSprint();
	/** Setter bisSprint */
	void set_bIsSprint(bool ValueToSet);
	/** Setter bisOn */
	void set_bIsOn();
	/**Tick */
	virtual void Tick(float DeltaTime) override;

	void AddItemToInventory(APickupActor* InPickupActor);

	void RemoveItemFromInventory(APickupActor* InItem);
protected:
	/** Check if flashlight is on */
	bool bisOn = false;
	/** Check if player is holding sprint button */
	bool bisSprint = false;
	/** Check if it's playing breath sound */
	bool bPlayBreath = false;
	/** Check if it's playing recovery sound */
	bool bPlayHeal = false;
private:
};

