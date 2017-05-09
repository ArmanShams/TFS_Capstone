// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "MyAIController.generated.h"

UCLASS()
class LONEWOLF_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	
	AMyAIController();

	virtual void Possess(APawn* InPawn) override;

	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

protected:

	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTreeAsset;

	
};
