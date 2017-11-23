// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"
#include "Pedo.generated.h"

UCLASS()
class DONTLETHIMSEEYOU_API APedo : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APedo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		class UParticleSystemComponent* Amaterasu;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
		bool bisAlive;
};
