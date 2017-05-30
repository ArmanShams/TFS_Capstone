// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "EnemyAI/Sheriff/SheriffAIController.h"
#include "EnemyAI/Sheriff/SheriffAI.h"
#include "BTTask_SheriffCasting.h"

UBTTask_SheriffCasting::UBTTask_SheriffCasting()
{
}

EBTNodeResult::Type UBTTask_SheriffCasting::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* BehaviorTree = &OwnerComp;
	if (ASheriffAIController* Controller = Cast<ASheriffAIController>(BehaviorTree->GetAIOwner()))
	{
		//Cast<ASheriffAI>(Controller->GetPawn())->Casting();
		Cast<ASheriffAI>(Controller->GetPawn())->SetSheriffState(SheriffState::CASTING);
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTask_SheriffCasting::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}