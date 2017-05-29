// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BTTask_SheriffFlee.h"
#include "EnemyAI/Sheriff/SheriffAI.h"
#include "EnemyAI/Sheriff/SheriffAIController.h"

UBTTask_SheriffFlee::UBTTask_SheriffFlee()
{
}

EBTNodeResult::Type UBTTask_SheriffFlee::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* BehaviorTree = &OwnerComp;
	if (ASheriffAIController* Controller = Cast<ASheriffAIController>(BehaviorTree->GetAIOwner()))
	{
		Cast<ASheriffAI>(Controller->GetPawn())->SetSheriffState(SheriffState::FLEEING);
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTask_SheriffFlee::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}
