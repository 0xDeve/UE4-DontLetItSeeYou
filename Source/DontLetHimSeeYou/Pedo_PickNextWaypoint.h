// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Pedo_PickNextWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class DONTLETHIMSEEYOU_API UPedo_PickNextWaypoint : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector Index;
	UPROPERTY(EditAnywhere, Category = "Blackboard")
		struct FBlackboardKeySelector Waypoint;
};
