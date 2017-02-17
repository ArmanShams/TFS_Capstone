// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Enemy.h"
#include "MyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "GenericTeamAgentInterface.h"

AMyAIController::AMyAIController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));

}

void AMyAIController::Possess(APawn * InPawn)
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

ETeamAttitude::Type AMyAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (Cast<IGenericTeamAgentInterface>(&Other))
	{
		return Super::GetTeamAttitudeTowards(Other);
	}
	
	return ETeamAttitude::Hostile;
}
