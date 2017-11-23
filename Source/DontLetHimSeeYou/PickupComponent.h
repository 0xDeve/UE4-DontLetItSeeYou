// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Components/ActorComponent.h"
#include "PickupBattery.h"
#include "PickupComponent.generated.h"

class ADontLetHimSeeYouCharacter;
class UPickupBattery;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DONTLETHIMSEEYOU_API UPickupComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickupComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/** Pickup function */
	UFUNCTION(BlueprintCallable, Category = "Pickup component")
		const FHitResult LineTrace();
	UFUNCTION(BlueprintCallable, Category = "Pickup component")
		bool PickUpSharingan(FHitResult HitResult);
	UFUNCTION(BlueprintCallable, Category = "Pickup component")
		bool ActivateAmaterasu(FHitResult HitResult);
	UFUNCTION(BlueprintCallable, Category = "Pickup component")
		bool PickUpKunai(FHitResult HitResult);
	UFUNCTION(BlueprintCallable, Category = "Pickup component")
		void Teleport();
	UPROPERTY(EditAnywhere, Category = "Teleport points")
		TSubclassOf<AActor> ClassToFind;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Teleport points")
		TArray<AActor*> TargetPoints;
	UFUNCTION(BlueprintCallable, Category = "Pickup component")
		bool PickUpRockWallJutsu(FHitResult HitResult);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
		class USoundBase* PickupBatteryVFX;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup component")
		int32 numSkill = 3;
private:
	// How far a player can reach to the battery	
	float ReachDistance = 800.f;

	/** Get trace start location */
	FVector GetReachLineStart();
	/** Get trace end location */
	FVector GetReachLineEnd();

	void PickUpBattery(FHitResult HitResult);
	bool bHasAmaterasu = false;
	bool bHasKunai = false;
	bool bHasScroll = false; 
};
