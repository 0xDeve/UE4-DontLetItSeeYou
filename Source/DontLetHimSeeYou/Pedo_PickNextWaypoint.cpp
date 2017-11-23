// Fill out your copyright notice in the Description page of Project Settings.

#include "Pedo_PickNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Pedo_PatrollingComp.h"

EBTNodeResult::Type UPedo_PickNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get controlled pawn
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	// Get patrol component
	auto PatrolComp = ControlledPawn->FindComponentByClass<UPedo_PatrollingComp>();
	// Check if there is a patrol comp
	if (!ensure(PatrolComp)) return EBTNodeResult::Failed;
	// Get patrol points
	auto PatrolPoints = PatrolComp->GetPatrolPoints();
	if (PatrolPoints.Num() == 0) {
		//UE_LOG(LogTemp, Warning, TEXT("No patrol points found"));
		return EBTNodeResult::Failed;
	}
	//
	// Set next waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto IndexKey = BlackboardComp->GetValueAsInt(Index.SelectedKeyName);
	BlackboardComp->SetValueAsObject(Waypoint.SelectedKeyName, PatrolPoints[IndexKey]);

	auto NextIndex = FMath::RandRange((int32)0, (int32)PatrolPoints.Num());
	BlackboardComp->SetValueAsInt(Index.SelectedKeyName, NextIndex);
	return EBTNodeResult::Succeeded;

}


