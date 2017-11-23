// Fill out your copyright notice in the Description page of Project Settings.

#include "Pedo.h"

// Sets default values
APedo::APedo()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Amaterasu = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Amaterasu"));
	Amaterasu->SetupAttachment(GetMesh(), TEXT("Amaterasu"));
	
}

// Called when the game starts or when spawned
void APedo::BeginPlay()
{
	Super::BeginPlay();
	bisAlive = true;
}

// Called every frame
void APedo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APedo::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

