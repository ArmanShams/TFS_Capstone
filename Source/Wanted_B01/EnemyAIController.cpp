// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "Perception/AIPerceptionComponent.h"


AEnemyAIController::AEnemyAIController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
}

void AEnemyAIController::Possess(APawn* InPawn)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(InPawn))
	{
		if (BehaviorTreeAsset)
		{

		}
	}
}

void AEnemyAIController::UnPossess()
{

}
