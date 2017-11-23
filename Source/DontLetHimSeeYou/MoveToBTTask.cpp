// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveToBTTask.h"
#include "DontLetHimSeeYouCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

EBTNodeResult::Type UMoveToBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto AIController = OwnerComp.GetAIOwner(); // Get AI Controller
	auto BlackBoardComp = OwnerComp.GetBlackboardComponent(); // Get black board comp
	auto Actor = BlackBoardComp->GetValueAsObject(ActorKey.SelectedKeyName); // Get Runner reference
	auto PlayerActor = Cast<class ADontLetHimSeeYouCharacter>(Actor); // Cast to Actor type
	auto ControlledPawn = AIController->GetPawn(); // Get AI pawn
	
	auto AILocation = ControlledPawn->GetActorLocation(); // Get location of AI
	auto PlayerLocation = PlayerActor->GetActorLocation(); // Get location of runner
	AIController->MoveToActor(PlayerActor, 10.f, false, true); // AI move to runner when in sight
	if (FMath::Abs((AILocation - PlayerLocation).Size()) < 250) {
		// If distance between AI and runner < 8 then destroy runner
		//PlayerActor->Destroy();
		PlayerActor->bisDead = true;
	}
	return EBTNodeResult::Succeeded;
}


