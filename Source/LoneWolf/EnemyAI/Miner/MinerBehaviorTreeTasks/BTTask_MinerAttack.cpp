// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BTTask_MinerAttack.h"
#include "EnemyAI/Miner/MinerAIController.h"
#include "EnemyAI/Miner/MinerAI.h"

UBTTask_MinerAttack::UBTTask_MinerAttack()
{

}

EBTNodeResult::Type UBTTask_MinerAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* BehaviorTree = &OwnerComp;
	if (AMinerAIController* Controller = Cast<AMinerAIController>(BehaviorTree->GetAIOwner()))
	{
		Cast<AMinerAI>(Controller->GetPawn())->Attack();
	}

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTask_MinerAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}
