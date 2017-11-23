// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CheckIfAlive_BBTask.generated.h"

/**
 * 
 */
UCLASS()
class DONTLETHIMSEEYOU_API UCheckIfAlive_BBTask : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UPROPERTY(EditAnywhere, Category = "Status")
		struct FBlackboardKeySelector isAliveKey;
};
