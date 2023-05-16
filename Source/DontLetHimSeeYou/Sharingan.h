// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupActor.h"
#include "Sharingan.generated.h"

UCLASS()
class DONTLETHIMSEEYOU_API ASharingan : public APickupActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASharingan();

	UPROPERTY(EditAnywhere, Category = "VFX")
	UParticleSystem* FireParticle;

	// ~APickupActor interface
	void OnPickup_Implementation(class ADontLetHimSeeYouCharacter* InInteractor) override;
	void ActivateSkill_Implementation() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
