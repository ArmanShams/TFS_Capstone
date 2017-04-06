// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "BTTask_MinerCharge.h"
#include "EnemyAI/Miner/MinerAIController.h"
#include "EnemyAI/Miner/MinerAI.h"



UBTTask_MinerCharge::UBTTask_MinerCharge()
{

}

EBTNodeResult::Type UBTTask_MinerCharge::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* BehaviorTree = &OwnerComp;
	if (AMinerAIController* Controller = Cast<AMinerAIController>(BehaviorTree->GetAIOwner()))
	{
		Cast<AMinerAI>(Controller->GetPawn())->Charge();
	}

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTask_MinerCharge::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}
