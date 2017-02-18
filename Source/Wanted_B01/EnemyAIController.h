// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_B01_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAIController();
	virtual void Possess(APawn* InPawn) override;
	virtual void UnPossess() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTree* BehaviorTreeAsset;
	
};
