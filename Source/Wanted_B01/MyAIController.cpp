// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Enemy.h"
#include "MyAIController.h"

AMyAIController::AMyAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));

}

void AMyAIController::Possess(APawn * InPawn)
{
	if (AEnemy* Enemy = Cast<AEnemy>(InPawn))
	{
		if (BehaviorTreeAsset)
		{
			BlackboardComponent->InitializeBlackboard(*BehaviorTreeAsset->BlackboardAsset);
			BehaviorTreeComponent->StartTree(*BehaviorTreeAsset);
		}
	}
}

void AMyAIController::UnPossess()
{
	if (BehaviorTreeComponent->IsRunning())
	{
		BehaviorTreeComponent->StopTree();
	}
}
