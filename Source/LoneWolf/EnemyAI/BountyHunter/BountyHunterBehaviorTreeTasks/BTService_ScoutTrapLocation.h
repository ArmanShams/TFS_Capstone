// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTService.h"
#include "BTService_ScoutTrapLocation.generated.h"

/**
 * 
 */
UCLASS()
class LONEWOLF_API UBTService_ScoutTrapLocation : public UBTService
{
	GENERATED_BODY()
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	int32 LocationPoint;

};
