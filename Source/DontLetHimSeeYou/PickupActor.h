// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupActor.generated.h"

UCLASS()
class DONTLETHIMSEEYOU_API APickupActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* PickupMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class USoundBase* PickupSoundEffect;

	FORCEINLINE UStaticMeshComponent* GetMesh() { return PickupMeshComponent; }

	UFUNCTION(BlueprintNativeEvent)
	void OnPickup(class ADontLetHimSeeYouCharacter* InInteractor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ActivateSkill();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
