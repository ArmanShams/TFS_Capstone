// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MinerCharge.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_B01_API UBTTask_MinerCharge : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_MinerCharge();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	friend class AMinerAI;
	
};
