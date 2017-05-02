// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SheriffRevolverAttack.generated.h"

UCLASS()
class LONEWOLF_API UBTTask_SheriffRevolverAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_SheriffRevolverAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	friend class ASheriffAI;

};
