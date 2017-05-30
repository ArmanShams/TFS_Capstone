// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BTTask_BartenderThrowMolotov.h"
#include "EnemyAI/Bartender/BartenderAI.h"
#include "EnemyAI/Bartender/BartenderAIController.h"


UBTTask_BartenderThrowMolotov::UBTTask_BartenderThrowMolotov()
{

}

EBTNodeResult::Type UBTTask_BartenderThrowMolotov::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBehaviorTreeComponent* BehaviorTree = &OwnerComp;
	if (ABartenderAIController* Controller = Cast<ABartenderAIController>(BehaviorTree->GetAIOwner()))
	{
		Cast<ABartenderAI>(Controller->GetPawn())->SetIsAttacking(true);
	}
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

EBTNodeResult::Type UBTTask_BartenderThrowMolotov::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);
}
