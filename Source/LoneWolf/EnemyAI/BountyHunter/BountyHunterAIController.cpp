// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BehaviorTree//BehaviorTree.h"
#include "EnemyAI/BountyHunter/BountyHunter.h"
#include "Perception/AIPerceptionComponent.h"
#include "BountyHunterAIController.h"
#include "GenericTeamAgentInterface.h"

ABountyHunterAIController::ABountyHunterAIController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
}

void ABountyHunterAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);
	if (ABountyHunter* BountyHunter = Cast<ABountyHunter>(InPawn))
	{
		if (BountyHunterBTAsset)
		{
			RunBehaviorTree(BountyHunterBTAsset);
		}
	}
}

ETeamAttitude::Type ABountyHunterAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (Cast<IGenericTeamAgentInterface>(&Other))
	{
		return Super::GetTeamAttitudeTowards(Other);
	}
	return ETeamAttitude::Hostile;
}
