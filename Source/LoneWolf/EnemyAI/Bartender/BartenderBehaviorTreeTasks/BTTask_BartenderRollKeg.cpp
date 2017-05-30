// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BTTask_BartenderRollKeg.h"
#include "EnemyAI/Bartender/BartenderAI.h"
#include "EnemyAI/Bartender/BartenderAIController.h"


UBTTask_BartenderRollKeg::UBTTask_BartenderRollKeg()
{
	
}

EBTNodeResult::Type UBTTask_BartenderRollKeg::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* BehaviorTree = &OwnerComp;
	if (ABartenderAIController* Controller = Cast<ABartenderAIController>(BehaviorTree->GetAIOwner()))
	{
		Cast<ABartenderAI>(Controller->GetPawn())->RollKeg();
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTask_BartenderRollKeg::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}
