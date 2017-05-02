// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "EnemyAI/Sheriff/SheriffAIController.h"
#include "EnemyAI/Sheriff/SheriffAI.h"
#include "BTTask_SheriffKnifeAttack.h"

UBTTask_SheriffKnifeAttack::UBTTask_SheriffKnifeAttack()
{
}

EBTNodeResult::Type UBTTask_SheriffKnifeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* BehaviorTree = &OwnerComp;
	if (ASheriffAI* Controller = Cast<ASheriffAI>(BehaviorTree->GetAIOwner()))
	{
		// Cast<ASheriffAI>(Controller->GetPawn())->KnifeAttack();
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTask_SheriffKnifeAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}
