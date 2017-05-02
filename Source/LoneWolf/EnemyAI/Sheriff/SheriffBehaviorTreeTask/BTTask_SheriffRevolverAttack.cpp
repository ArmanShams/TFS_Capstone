// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "EnemyAI/Sheriff/SheriffAIController.h"
#include "EnemyAI/Sheriff/SheriffAI.h"
#include "BTTask_SheriffRevolverAttack.h"

UBTTask_SheriffRevolverAttack::UBTTask_SheriffRevolverAttack()
{
}

EBTNodeResult::Type UBTTask_SheriffRevolverAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* BehaviorTree = &OwnerComp;
	if (ASheriffAI* Controller = Cast<ASheriffAI>(BehaviorTree->GetAIOwner()))
	{
		// Cast<ASheriffAI>(Controller->GetPawn())->RevolverAttack();
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTask_SheriffRevolverAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}
