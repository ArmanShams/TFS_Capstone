// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BTService_FindTarget.h"
#include "AIController.h"
#include "Character/PlayerCharacter/CharacterController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/PlayerState.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "EnemyAI/Enemy.h"
#include "Engine/TargetPoint.h"


void UBTService_FindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UAIPerceptionComponent* PerceptionComponent = OwnerComp.GetAIOwner()->GetPerceptionComponent();

	TArray<ATargetPoint*> PatrolPoints = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn())->PatrolPoints;
	TArray<AActor*> HostileActors;
	PerceptionComponent->GetPerceivedHostileActors(HostileActors);
	if (HostileActors.Num() > 0)
	{
		// Cancels current movement task if the AI is patrolling.
		if (Cast<ATargetPoint>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target"))))
		{
			//UE_LOG(LogTemp, Display, TEXT("We are in the beam"));
			OwnerComp.GetAIOwner()->StopMovement();
		}
		AActor* HostileActor = NULL; 
		for (int i = 0; i < HostileActors.Num(); i++)
		{
			if (Cast<ACharacterController>(HostileActors[i]))
			{
				HostileActor = HostileActors[i];
			}
		}

		if (HostileActor != NULL)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), Cast<AActor>(HostileActor));
		}
		return;
	}

	else if(PatrolPoints.Num() > 0)
	{
		
		RangePoint = FMath::RandRange(0, PatrolPoints.Num() - 1);
		AActor* PatrolPoint = PatrolPoints[RangePoint];
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), PatrolPoint);
		return;
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), NULL);
	OwnerComp.GetAIOwner()->StopMovement();
}



