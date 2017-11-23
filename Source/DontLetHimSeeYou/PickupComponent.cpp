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
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner()); // Collision settings
	auto isHit = GetWorld()->LineTraceSingleByObjectType( // Return true if trace hits something
		HitResult, // OUT hit result
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), // Return true if trace hits a physicsbody collision present
		TraceParameters
	);
	PickUpBattery(HitResult);
	return HitResult;
}

void UPickupComponent::PickUpBattery(FHitResult HitResult)
{
	auto HitActor = HitResult.GetActor();
	auto BatteryPickup = Cast<APickupBattery>(HitActor);
	if (HitActor && BatteryPickup && PickupBatteryVFX != NULL) {
		HitActor->Destroy(); // Destroy component and increase battery
							 // Increase the battery of flashlight
		UGameplayStatics::PlaySoundAtLocation(this, PickupBatteryVFX, BatteryPickup->GetActorLocation());
		auto Character = Cast<ADontLetHimSeeYouCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		if (Character) {
			Character->IncreaseBattery(20);
			// Increase by time
		}
		else UE_LOG(LogTemp, Warning, TEXT("Cast failed"));
	}
}

bool UPickupComponent::PickUpSharingan(FHitResult HitResult)
{
	auto HitActor = HitResult.GetActor();
	auto SharinganPickup = Cast<ASharingan>(HitActor);
	if (numSkill > 0 && bHasAmaterasu == false) {
		if (HitActor && SharinganPickup) {
			HitActor->Destroy();
			bHasAmaterasu = true;
			ReachDistance = 5000.f;
			numSkill--;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

bool UPickupComponent::PickUpKunai(FHitResult HitResult)
{
	auto HitActor = HitResult.GetActor();
	auto KunaiPickup = Cast<ATeleportationJutsu>(HitActor);
	if (numSkill > 0 && bHasKunai == false) {
		if (HitActor && KunaiPickup) {
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, TargetPoints);
			bHasKunai = true;
			KunaiPickup->Destroy();
			numSkill--;
			return true;
		}
		else return false;
	}
	return false;
}

bool UPickupComponent::PickUpRockWallJutsu(FHitResult HitResult)
{
	auto HitActor = HitResult.GetActor();
	auto Acquire = Cast<ARockWallJutsu>(HitActor);
	if (numSkill > 0 && bHasScroll == false) {
		if (HitActor && Acquire) {
			Acquire->Destroy();
			bHasScroll = true;
			numSkill--;
			return true;
		}
		else return false;
	}
	return false;
}

void UPickupComponent::Teleport()
{
	if (bHasKunai) {
		int32 Index = FMath::RandRange((int32)0, (int32)TargetPoints.Num());
		auto TeleLocation = TargetPoints[Index]->GetActorLocation();
		 GetOwner()->SetActorLocation(TeleLocation);
		 numSkill++;
		 bHasKunai = false;
	}
}

bool UPickupComponent::ActivateAmaterasu(FHitResult HitResult)
{
	auto HitActor = HitResult.GetActor();
	auto Activation = Cast<APedo>(HitActor);
	
	if (HitActor && Activation && bHasAmaterasu) {
		auto FireRef = Activation->Amaterasu;
		FireRef->ActivateSystem(true);
		bHasAmaterasu = false;
		ReachDistance = 800.f;
		Activation->bisAlive = false;
		numSkill++;
		return true;
	}
	else if (HitActor){
		UE_LOG(LogTemp, Warning, TEXT("Actor hit"));
		return false;
	}
	else if (Activation) {
		UE_LOG(LogTemp, Warning, TEXT("Cast succeeded"));
		return false;
	}
	else return false;
}
