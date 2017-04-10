// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "BTService_FindTarget.h"
#include "AIController.h"
#include "Character/CharacterController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/PlayerState.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Enemy.h"
#include "Engine/TargetPoint.h"


void UBTService_FindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UAIPerceptionComponent* PerceptionComponent = OwnerComp.GetAIOwner()->GetPerceptionComponent();

	TArray<ATargetPoint*> PatrolPoints = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn())->PatrolPoints;
	bool SetPatrol = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn())->SetPatrol;
	TArray<AActor*> HostileActors;
	PerceptionComponent->GetPerceivedHostileActors(HostileActors);

	if (HostileActors.Num() > 0)
	{
		if (test == 1)
		{
			OwnerComp.GetAIOwner()->StopMovement();
			test = 0;
		}
		AActor* HostileActor = NULL; //= HostileActors[0];
		
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

	if (SetPatrol)
	{
		if (HostileActors.Num() == 0 && PatrolPoints.Num() > 0)
		{
			if (test == 0)
			{
				OwnerComp.GetAIOwner()->StopMovement();
				test = 1;
			}
			RangePoint = FMath::RandRange(0, PatrolPoints.Num() - 1);
			AActor* PatrolPoint = PatrolPoints[RangePoint];
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), PatrolPoint);
			return;
		}
	}
	if (!SetPatrol)
	{
		if (HostileActors.Num() == 0 && PatrolPoints.Num() > 0)
		{
			if (test == 0)
			{
				OwnerComp.GetAIOwner()->StopMovement();
				test = 1;
			}
			if (CurrentPoint == PatrolPoints.Num() - 1)
			{
				RangePoint = 0;
				CurrentPoint = 0;
			}
			else
			{
				RangePoint = CurrentPoint + 1;
				CurrentPoint = RangePoint;
			}
			
			UE_LOG(LogTemp, Warning, TEXT("CurrentPoint is is %i"), CurrentPoint);

			AActor* PatrolPoint = PatrolPoints[RangePoint];
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), PatrolPoint);
			return;
		}
	}


	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), NULL);
	OwnerComp.GetAIOwner()->StopMovement();
}



