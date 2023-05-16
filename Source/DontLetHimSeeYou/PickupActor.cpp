// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActor.h"
#include "Components/StaticMeshComponent.h"
#include "DontLetHimSeeYouCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickupActor::APickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Mesh Component"));
	RootComponent = PickupMeshComponent;
}

void APickupActor::OnPickup_Implementation(class ADontLetHimSeeYouCharacter* InInteractor)
{
	if (PickupSoundEffect)
		UGameplayStatics::PlaySound2D(this, PickupSoundEffect);
	AttachToActor(InInteractor, FAttachmentTransformRules::SnapToTargetIncludingScale);
	SetActorHiddenInGame(true);
	PickupMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// Override in child classes
}

void APickupActor::ActivateSkill_Implementation()
{
	// Override in child classes
}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

