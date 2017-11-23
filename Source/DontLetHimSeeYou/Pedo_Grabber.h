// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Pedo_Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DONTLETHIMSEEYOU_API UPedo_Grabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPedo_Grabber();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Grab
	UFUNCTION(BlueprintCallable, Category= "Grab component")
	void Grab();

	// Called when finish grabbing
	UFUNCTION(BlueprintCallable, Category= "Grab component")
	void Release();
	
	// Find physics handle component
	void FindHandleComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// How far ahead of player can we reach
	float Reach = 200.f;
	
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	// Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	FVector GetReachLineStart();
	FVector GetReachLineEnd();
};
