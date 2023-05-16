// Fill out your copyright notice in the Description page of Project Settings.

#include "TeleportationJutsu.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATeleportationJutsu::ATeleportationJutsu()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATeleportationJutsu::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATeleportationJutsu::OnPickup_Implementation(class ADontLetHimSeeYouCharacter* InInteractor)
{	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, TeleportPoints);
	Super::OnPickup_Implementation(InInteractor);
}

// Called every frame
void ATeleportationJutsu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

