// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveToCustom.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_B01_API UBTTask_MoveToCustom : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
	
public:

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
