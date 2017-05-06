// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "EnemyAI/Sheriff/SheriffAI.h"
#include "EnemyAI/Sheriff/SheriffAIController.h"
#include "BTTask_SheriffShotgunAttack.h"

UBTTask_SheriffShotgunAttack::UBTTask_SheriffShotgunAttack()
{

}

EBTNodeResult::Type UBTTask_SheriffShotgunAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* BehaviorTree = &OwnerComp;
	if (ASheriffAIController* Controller = Cast<ASheriffAIController>(BehaviorTree->GetAIOwner()))
	{
		Cast<ASheriffAI>(Controller->GetPawn())->Shoot();
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTask_SheriffShotgunAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}