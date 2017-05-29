// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SheriffFlee.generated.h"

UCLASS()
class LONEWOLF_API UBTTask_SheriffFlee : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_SheriffFlee();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

protected:
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	friend class ASheriffAI;
};
