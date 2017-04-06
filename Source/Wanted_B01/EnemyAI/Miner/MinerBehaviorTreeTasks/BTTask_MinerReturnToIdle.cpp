// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "BTTask_MinerReturnToIdle.h"




UBTTask_MinerReturnToIdle::UBTTask_MinerReturnToIdle()
{

}

EBTNodeResult::Type UBTTask_MinerReturnToIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* BehaviorTree = &OwnerComp;
	if (AMinerAIController* Controller = Cast<AMinerAIController>(BehaviorTree->GetAIOwner()))
	{
		Cast<AMinerAI>(Controller->GetPawn())->SetMinerState(MinerState::IDLE);
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTask_MinerReturnToIdle::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}
