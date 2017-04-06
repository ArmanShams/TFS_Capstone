// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MinerAttack.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_B01_API UBTTask_MinerAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_MinerAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	friend class AMinerAI;
	
};
