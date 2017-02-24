// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_FindTarget.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_B01_API UBTS_FindTarget : public UBTService_BlackboardBase
{
	GENERATED_BODY()

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


	
	
};
