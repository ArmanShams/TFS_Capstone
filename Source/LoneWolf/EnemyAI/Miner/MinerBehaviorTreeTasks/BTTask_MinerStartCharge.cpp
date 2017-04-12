// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BTTask_MinerStartCharge.h"
#include "EnemyAI/Miner/MinerAIController.h"
#include "EnemyAI/Miner/MinerAI.h"

UBTTask_MinerStartCharge::UBTTask_MinerStartCharge()
{

}

EBTNodeResult::Type UBTTask_MinerStartCharge::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* BehaviorTree = &OwnerComp;
	if (AMinerAIController* Controller = Cast<AMinerAIController>(BehaviorTree->GetAIOwner()))
	{
		Cast<AMinerAI>(Controller->GetPawn())->StartCharge();
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTask_MinerStartCharge::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}
