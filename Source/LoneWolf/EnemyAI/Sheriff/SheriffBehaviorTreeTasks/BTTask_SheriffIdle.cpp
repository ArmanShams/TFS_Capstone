// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "EnemyAI/Sheriff/SheriffAIController.h"
#include "EnemyAI/Sheriff/SheriffAI.h"
#include "BTTask_SheriffIdle.h"

UBTTask_SheriffIdle::UBTTask_SheriffIdle()
{
}

EBTNodeResult::Type UBTTask_SheriffIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* BehaviorTree = &OwnerComp;
	if (ASheriffAIController* Controller = Cast<ASheriffAIController>(BehaviorTree->GetAIOwner()))
	{
		Cast<ASheriffAI>(Controller->GetPawn())->SetSheriffState(SheriffState::IDLE);
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTask_SheriffIdle::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}
