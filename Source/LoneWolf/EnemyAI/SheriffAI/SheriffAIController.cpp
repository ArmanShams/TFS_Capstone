// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BehaviorTree//BehaviorTree.h"
#include "SheriffAI.h"
#include "Perception/AIPerceptionComponent.h"
#include "GenericTeamAgentInterface.h"
#include "SheriffAIController.h"

ASheriffAIController::ASheriffAIController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
}

void ASheriffAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	if (ASheriffAI* SheriffAI = Cast<ASheriffAI>(InPawn))
	{
		if (SheriffBehaviorTreeAsset)
		{
			RunBehaviorTree(SheriffBehaviorTreeAsset);
		}
	}
}

ETeamAttitude::Type ASheriffAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (Cast<IGenericTeamAgentInterface>(&Other))
	{
		return Super::GetTeamAttitudeTowards(Other);
	}
	return ETeamAttitude::Hostile;
}
