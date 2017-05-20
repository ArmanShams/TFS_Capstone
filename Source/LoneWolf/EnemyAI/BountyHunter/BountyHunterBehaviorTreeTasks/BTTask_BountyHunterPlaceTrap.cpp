// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BTTask_BountyHunterPlaceTrap.h"
#include "EnemyAI/BountyHunter/BountyHunter.h"
#include "EnemyAI/BountyHunter/BountyHunterAIController.h"

UBTTask_BountyHunterPlaceTrap::UBTTask_BountyHunterPlaceTrap()
{
}

EBTNodeResult::Type UBTTask_BountyHunterPlaceTrap::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* BehaviorTree = &OwnerComp;
	if (ABountyHunterAIController* Controller = Cast<ABountyHunterAIController>(BehaviorTree->GetAIOwner()))
	{
		Cast<ABountyHunter>(Controller->GetPawn())->SetBountyHunterState(BountyHunterState::SETTINGTRAP);
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTask_BountyHunterPlaceTrap::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//UBehaviorTreeComponent* BehaviorTree = &OwnerComp;
	//if (ABountyHunterAIController* Controller = Cast<ABountyHunterAIController>(BehaviorTree->GetAIOwner()))
	//{
	//	Cast<ABountyHunter>(Controller->GetPawn())->SetBountyHunterState(BountyHunterState::IDLE);
	//}
	return Super::AbortTask(OwnerComp, NodeMemory);
}