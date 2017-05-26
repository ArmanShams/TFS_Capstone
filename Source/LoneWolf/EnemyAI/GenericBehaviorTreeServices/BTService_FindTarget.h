// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_FindTarget.generated.h"


UCLASS()
class LONEWOLF_API UBTService_FindTarget : public UBTService_BlackboardBase
{
	GENERATED_BODY()

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	bool bPawnPatrolsLinearly;
	int32 PatrolPointIterator = 0;
	int32 RangePoint;

};
