// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "BTService_FindTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/PlayerState.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"

void UBTService_FindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UAIPerceptionComponent* PerceptionComponent = OwnerComp.GetAIOwner()->GetPerceptionComponent();

	TArray<AActor*> HostileActors;
	PerceptionComponent->GetPerceivedHostileActors(HostileActors);

	if (HostileActors.Num() > 0)
	{
		AActor* HostileActor = HostileActors[0];
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), HostileActor);
		return;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), NULL);
	OwnerComp.GetAIOwner()->StopMovement();
}


