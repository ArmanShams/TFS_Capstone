// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "SheriffAIController.generated.h"

UCLASS()
class LONEWOLF_API ASheriffAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASheriffAIController();

	virtual void Possess(APawn* InPawn) override;
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

protected:
	UPROPERTY(EditDefaultsOnly)
		class UBehaviorTree* SheriffBehaviorTreeAsset;
};
