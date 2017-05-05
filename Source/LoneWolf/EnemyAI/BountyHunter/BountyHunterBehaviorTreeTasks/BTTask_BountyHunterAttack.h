// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BountyHunterAttack.generated.h"

/**
 * 
 */
UCLASS()
class LONEWOLF_API UBTTask_BountyHunterAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_BountyHunterAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	friend class ABountyHunter;

};
