// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BartenderThrowMolotov.generated.h"

/**
 * 
 */
UCLASS()
class LONEWOLF_API UBTTask_BartenderThrowMolotov : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_BartenderThrowMolotov();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	friend class ABartenderAI;
};
