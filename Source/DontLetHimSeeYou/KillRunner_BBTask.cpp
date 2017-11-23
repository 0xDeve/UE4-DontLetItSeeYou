// Fill out your copyright notice in the Description page of Project Settings.

#include "KillRunner_BBTask.h"
#include "AIController.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Pedo.h"
#include "TimerManager.h"

EBTNodeResult::Type UKillRunner_BBTask::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	PedoToKill = Cast<class APedo>(ControlledPawn);
	if (PedoToKill) {
		//GetWorld()->GetTimerManager().SetTimer(Timer, [&] {Pedo->Destroy(); }, 6.0f, false);
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UKillRunner_BBTask::DestroyPedo, 6.0f, false);
		PedoToKill->bisAlive = false;
	}
	return EBTNodeResult::Succeeded;
}

void UKillRunner_BBTask::DestroyPedo()
{
	PedoToKill->Destroy();
	
}