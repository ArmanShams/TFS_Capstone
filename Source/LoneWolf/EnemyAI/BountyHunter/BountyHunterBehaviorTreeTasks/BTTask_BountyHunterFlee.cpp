// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BTTask_BountyHunterFlee.h"
#include "EnemyAI/BountyHunter/BountyHunter.h"
#include "EnemyAI/BountyHunter/BountyHunterAIController.h"

UBTTask_BountyHunterFlee::UBTTask_BountyHunterFlee()
{
}

EBTNodeResult::Type UBTTask_BountyHunterFlee::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* BehaviorTree = &OwnerComp;
	if (ABountyHunterAIController* Controller = Cast<ABountyHunterAIController>(BehaviorTree->GetAIOwner()))
	{
		Cast<ABountyHunter>(Controller->GetPawn())->SetBountyHunterState(BountyHunterState::FLEEING);
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTask_BountyHunterFlee::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}
