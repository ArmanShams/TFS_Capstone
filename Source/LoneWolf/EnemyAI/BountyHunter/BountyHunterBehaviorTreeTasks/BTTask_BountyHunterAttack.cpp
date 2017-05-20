// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BTTask_BountyHunterAttack.h"
#include "EnemyAI/BountyHunter/BountyHunter.h"
#include "EnemyAI/BountyHunter/BountyHunterAIController.h"


UBTTask_BountyHunterAttack::UBTTask_BountyHunterAttack()
{
}

EBTNodeResult::Type UBTTask_BountyHunterAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* BehaviorTree = &OwnerComp;
	if (ABountyHunterAIController* Controller = Cast<ABountyHunterAIController>(BehaviorTree->GetAIOwner()))
	{
		//UE_LOG(LogTemp, Display, TEXT("WE ARE IN THE BEAM"));
		Cast<ABountyHunter>(Controller->GetPawn())->SetBountyHunterState(BountyHunterState::ATTACKING);
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTask_BountyHunterAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}
