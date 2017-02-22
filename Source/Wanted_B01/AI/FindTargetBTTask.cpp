// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/PlayerState.h"
#include "FindTargetBTTask.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"

EBTNodeResult::Type UFindTargetBTTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	UAIPerceptionComponent* PerceptionComponent = OwnerComp.GetAIOwner()->GetPerceptionComponent();

	TArray<AActor*> HostileActors;
	PerceptionComponent->GetPerceivedHostileActors(HostileActors);

	if (HostileActors.Num() > 0)
	{
		AActor* HostileActor = HostileActors[0];
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), HostileActor);
		return EBTNodeResult::Succeeded;
	}



	return EBTNodeResult::Failed;
}
