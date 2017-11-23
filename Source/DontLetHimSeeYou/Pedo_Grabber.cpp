// Fill out your copyright notice in the Description page of Project Settings.

#include "Pedo_Grabber.h"


// Sets default values for this component's properties
UPedo_Grabber::UPedo_Grabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bAutoActivate = true;
	// ...
}


// Called when the game starts
void UPedo_Grabber::BeginPlay()
{
	Super::BeginPlay();
	FindHandleComp();
	// ...
}
const FHitResult UPedo_Grabber::GetFirstPhysicsBodyInReach()
{
	/// Line-trace out to reach distance
	FHitResult HitResult;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	return HitResult;
}

FVector UPedo_Grabber::GetReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewPointLocation,
		PlayerViewPointRotation
	);
	return PlayerViewPointLocation;
}

FVector UPedo_Grabber::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewPointLocation,
		PlayerViewPointRotation
	);
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

void UPedo_Grabber::Grab()
{
	if (!PhysicsHandle) {
		return;
	}
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent(); // Get the mesh
	auto ActorHit = HitResult.GetActor();

	// If we hit something then attach a physics handle
	if (ActorHit) {
		PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation());
	}
}

void UPedo_Grabber::Release()
{
	if (!PhysicsHandle) {
		return;
	}
	PhysicsHandle->ReleaseComponent();
}

void UPedo_Grabber::FindHandleComp()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == NULL) {
		return;
	}

}


// Called every frame
void UPedo_Grabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!PhysicsHandle) return;
	
	if (PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
	// ...
}

