// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MoveToBTTask.generated.h"

/**
 * 
 */
UCLASS()
class DONTLETHIMSEEYOU_API UMoveToBTTask : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Target actors")
		struct FBlackboardKeySelector ActorKey;
};
