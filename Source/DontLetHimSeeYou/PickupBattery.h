// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupActor.h"
#include "PickupBattery.generated.h"

UCLASS()
class DONTLETHIMSEEYOU_API APickupBattery : public APickupActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupBattery();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ~APickupActor interface
	void OnPickup_Implementation(class ADontLetHimSeeYouCharacter* InInteractor) override;

	/** Return whether or not pickup is active */
	UFUNCTION(BlueprintPure, Category = "Pickup battery")
		bool IsActive();
	/** Allow other classes to safely change whether pickup is active or not */
	UFUNCTION(BlueprintCallable, Category = "Pickup battery")
		void SetActive(bool PickupState);
	UFUNCTION(BlueprintNativeEvent)
		void WasCollected();
	virtual void WasCollected_Implementation();
protected:
	bool bIsActive;

private:


	
};
