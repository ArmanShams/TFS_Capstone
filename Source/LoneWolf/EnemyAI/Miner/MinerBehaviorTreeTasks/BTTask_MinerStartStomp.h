// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MinerStartStomp.generated.h"

/**
 * 
 */
UCLASS()
class LONEWOLF_API UBTTask_MinerStartStomp : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_MinerStartStomp();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	friend class AMinerAI;
};
