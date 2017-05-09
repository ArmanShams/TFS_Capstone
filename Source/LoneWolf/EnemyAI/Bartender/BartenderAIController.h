// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BartenderAIController.generated.h"

/**
 * 
 */
UCLASS()
class LONEWOLF_API ABartenderAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABartenderAIController();

	virtual void Possess(APawn* InPawn) override;

	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

protected:
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTreeAsset;

	//class UAIPerceptionComponent NewPerceptionComponent;

	friend class AEnemy;
	
	
};
