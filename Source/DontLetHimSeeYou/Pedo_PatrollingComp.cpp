// Fill out your copyright notice in the Description page of Project Settings.

#include "Pedo_PatrollingComp.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
// Sets default values for this component's properties
UPedo_PatrollingComp::UPedo_PatrollingComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPedo_PatrollingComp::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), PatrolPoints);
	//UE_LOG(LogTemp, Warning, TEXT("%d"), PatrolPoints.Num());
}


// Called every frame
void UPedo_PatrollingComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<AActor*> UPedo_PatrollingComp::GetPatrolPoints() const
{
	return PatrolPoints;
}