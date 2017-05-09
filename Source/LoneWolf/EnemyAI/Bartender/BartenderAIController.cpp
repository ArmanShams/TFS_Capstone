// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BartenderAIController.h"



ABartenderAIController::ABartenderAIController()
{
	//NewPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	//SetPerceptionComponent(NewPerceptionComponent);
}

void ABartenderAIController::Possess(APawn* InPawn)
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

ETeamAttitude::Type ABartenderAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (Cast<IGenericTeamAgentInterface>(&Other))
	{
		return Super::GetTeamAttitudeTowards(Other);
	}

	return ETeamAttitude::Hostile;
}
