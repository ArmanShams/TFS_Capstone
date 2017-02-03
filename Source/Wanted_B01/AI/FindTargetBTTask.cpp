// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/PlayerState.h"
#include "FindTargetBTTask.h"

EBTNodeResult::Type UFindTargetBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	for (FConstPawnIterator PawnItr = GetWorld()->GetPawnIterator(); PawnItr; ++PawnItr)
	{
		APawn* Pawn = *PawnItr;
		if (Pawn == OwnerComp.GetAIOwner()->GetPawn() || (!Pawn->PlayerState || !Pawn->PlayerState->bIsABot))
		{
			continue;
		}

		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), Pawn);

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
