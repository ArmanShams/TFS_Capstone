// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BTTask_MinerStomp.h"




UBTTask_MinerStomp::UBTTask_MinerStomp()
{

}

EBTNodeResult::Type UBTTask_MinerStomp::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* BehaviorTree = &OwnerComp;
	if (AMinerAIController* Controller = Cast<AMinerAIController>(BehaviorTree->GetAIOwner()))
	{
		Cast<AMinerAI>(Controller->GetPawn())->Stomp();
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTask_MinerStomp::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}
