// Fill out your copyright notice in the Description page of Project Settings.

#include "Sharingan.h"


// Sets default values
ASharingan::ASharingan()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASharingan::ActivateSkill_Implementation()
{
	//ADontLetHimSeeYouCharacter* OwnerCharacter = GetOwner<()
}

void ASharingan::OnPickup_Implementation(class ADontLetHimSeeYouCharacter* InInteractor)
{

	Super::OnPickup_Implementation(InInteractor);
}

// Called when the game starts or when spawned
void ASharingan::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASharingan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

