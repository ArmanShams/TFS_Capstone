// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SheriffAttack.generated.h"

UCLASS()
class LONEWOLF_API UBTTask_SheriffAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_SheriffAttack();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

private:
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	friend class SheriffAI;
};
