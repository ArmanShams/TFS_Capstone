// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BTTask_BountyHunterReturnToIdle.h"

UBTTask_BountyHunterReturnToIdle::UBTTask_BountyHunterReturnToIdle()
{

}

EBTNodeResult::Type UBTTask_BountyHunterReturnToIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* BehaviorTree = &OwnerComp;
	if (AMinerAIController* Controller = Cast<AMinerAIController>(BehaviorTree->GetAIOwner()))
	{
		Cast<ABountyHunter>(Controller->GetPawn())->SetBountyHunterState(BountyHunterState::IDLE);
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTask_BountyHunterReturnToIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}