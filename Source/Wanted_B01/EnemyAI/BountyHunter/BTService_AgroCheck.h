// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTService.h"
#include "BTService_AgroCheck.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_B01_API UBTService_AgroCheck : public UBTService
{
	GENERATED_BODY()

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	int32 RangePoint;
	int32 test = 0;

};
