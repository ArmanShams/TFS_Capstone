// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BounterHunterAttack.generated.h"

/**
 * 
 */
UCLASS()
class LONEWOLF_API UBTTask_BounterHunterAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_BounterHunterAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	friend class ABountyHunter;
	
	
	
};
