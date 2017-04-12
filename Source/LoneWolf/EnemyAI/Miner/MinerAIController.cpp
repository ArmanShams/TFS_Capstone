// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyAI/Enemy.h"
#include "Perception/AIPerceptionComponent.h"
#include "GenericTeamAgentInterface.h"
#include "MinerAIController.h"

AMinerAIController::AMinerAIController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
}

void AMinerAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	if (AEnemy* Enemy = Cast<AEnemy>(InPawn))
	{
		if (BehaviorTreeAsset)
		{
			RunBehaviorTree(BehaviorTreeAsset);
		}
	}
}

ETeamAttitude::Type AMinerAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (Cast<IGenericTeamAgentInterface>(&Other))
	{
		return Super::GetTeamAttitudeTowards(Other);
	}

	return ETeamAttitude::Hostile;
}
