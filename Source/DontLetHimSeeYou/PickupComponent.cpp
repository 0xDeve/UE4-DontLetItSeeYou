// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupComponent.h"
#include "PickupBattery.h"
#include "Sharingan.h"
#include "Pedo.h"
#include "TeleportationJutsu.h"
#include "RockWallJutsu.h"
#include "DontLetHimSeeYouCharacter.h"

// Sets default values for this component's properties
UPickupComponent::UPickupComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UPickupComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
}


// Called every frame
void UPickupComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

FVector UPickupComponent::GetReachLineStart()
{
	FVector PlayerViewPointLocation; // Player camera location
	FRotator PlayerViewPointRotation; // Player camera rotation
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewPointLocation,
		PlayerViewPointRotation
	);
	return PlayerViewPointLocation;
}

FVector UPickupComponent::GetReachLineEnd()
{
	FVector PlayerViewPointLocation; // Player camera location
	FRotator PlayerViewPointRotation; // Player camera rotation
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewPointLocation,
		PlayerViewPointRotation
	);
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * ReachDistance;
}

const FHitResult UPickupComponent::LineTrace()
{
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());
	bool bIsHit = GetWorld()->LineTraceSingleByChannel(HitResult, GetReachLineStart(), GetReachLineEnd(), ECC_Visibility, QueryParams);
	if (bIsHit) {
		if (APickupActor* PickupActor = Cast<APickupActor>(HitResult.GetActor())) {
			if (ADontLetHimSeeYouCharacter* OwningCharacter = GetOwner<ADontLetHimSeeYouCharacter>()) {
				PickupActor->OnPickup(OwningCharacter);
				PickupActor->SetOwner(OwningCharacter);
				OwningCharacter->AddItemToInventory(PickupActor);
			}	
			// Reduce current skill slot
		}
	}
	return HitResult;
}
