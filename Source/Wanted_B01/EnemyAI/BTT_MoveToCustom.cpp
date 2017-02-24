// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "BTT_MoveToCustom.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"


void UBTT_MoveToCustom::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AActor* CurrentTarget = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(TEXT("Target")));

	//if ()
}
