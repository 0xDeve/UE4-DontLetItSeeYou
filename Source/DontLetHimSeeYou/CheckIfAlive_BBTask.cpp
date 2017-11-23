// Fill out your copyright notice in the Description page of Project Settings.

#include "CheckIfAlive_BBTask.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Pedo.h"

EBTNodeResult::Type UCheckIfAlive_BBTask::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();

	auto Pedo = Cast<class APedo>(ControlledPawn);
	if (Pedo) {
		bool IsAlive = Pedo->bisAlive;
		BlackboardComp->SetValueAsBool(isAliveKey.SelectedKeyName, IsAlive);
	}
	return EBTNodeResult::Succeeded;
}
