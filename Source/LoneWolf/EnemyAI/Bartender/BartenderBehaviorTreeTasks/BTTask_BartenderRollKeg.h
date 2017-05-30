// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BartenderRollKeg.generated.h"

/**
 * 
 */
UCLASS()
class LONEWOLF_API UBTTask_BartenderRollKeg : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_BartenderRollKeg();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	friend class ABartenderAI;
	
	
	
};
