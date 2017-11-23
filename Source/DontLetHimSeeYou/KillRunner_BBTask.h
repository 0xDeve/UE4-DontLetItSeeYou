// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "KillRunner_BBTask.generated.h"
/**
 * 
 */
UCLASS()
class DONTLETHIMSEEYOU_API UKillRunner_BBTask : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	FTimerHandle Timer;
private:
	class APedo* PedoToKill;
	void DestroyPedo();
};
