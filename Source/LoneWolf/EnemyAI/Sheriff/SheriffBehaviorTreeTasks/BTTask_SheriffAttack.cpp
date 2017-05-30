// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BTTask_SheriffAttack.h"
#include "EnemyAI/Sheriff/SheriffAIController.h"
#include "EnemyAI/Sheriff/SheriffAI.h"

UBTTask_SheriffAttack::UBTTask_SheriffAttack()
{
}

EBTNodeResult::Type UBTTask_SheriffAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* BehaviorTree = &OwnerComp;
	if (ASheriffAIController* Controller = Cast<ASheriffAIController>(BehaviorTree->GetAIOwner()))
	{
		Cast<ASheriffAI>(Controller->GetPawn())->SetSheriffState(SheriffState::ATTACKING);
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTask_SheriffAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}
