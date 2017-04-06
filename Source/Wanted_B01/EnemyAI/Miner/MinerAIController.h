// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "MinerAIController.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_B01_API AMinerAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMinerAIController();

	virtual void Possess(APawn* InPawn) override;

	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

protected:

	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTreeAsset;

	friend class AEnemy;
	
	
};
