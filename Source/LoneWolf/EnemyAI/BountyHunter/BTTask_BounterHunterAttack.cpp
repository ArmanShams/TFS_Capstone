// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BTTask_BounterHunterAttack.h"
#include "EnemyAI/BountyHunter/BountyHunter.h"
#include "EnemyAI/BountyHunter/BountyHunterAIController.h"


UBTTask_BounterHunterAttack::UBTTask_BounterHunterAttack()
{

}

EBTNodeResult::Type UBTTask_BounterHunterAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* BehaviorTree = &OwnerComp;
	if (ABountyHunterAIController* Controller = Cast<ABountyHunterAIController>(BehaviorTree->GetAIOwner()))
	{
		Cast<ABountyHunter>(Controller->GetPawn())->Attack();
	}

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTask_BounterHunterAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}
