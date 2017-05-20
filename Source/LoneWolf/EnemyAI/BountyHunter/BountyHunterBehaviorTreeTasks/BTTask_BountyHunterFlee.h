// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BountyHunterFlee.generated.h"

UCLASS()
class LONEWOLF_API UBTTask_BountyHunterFlee : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_BountyHunterFlee();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

protected:
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	friend class ABountyHunter;
};
