// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "EnemyAI/RangedAI.h"
#include "RangedAnimInstance.h"

void URangedAnimInstance::NativeUpdateAnimation(float DeltaSeconds) 
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	{
		//	TryGetPawnOwner: Targets the AnimInstance Reference and returns the value of pawn reference 
		if (ARangedAI* RangedAI = Cast<ARangedAI>(TryGetPawnOwner())) {
			MovementSpeed = RangedAI->GetVelocity().Size();
		}
	}
}

void URangedAnimInstance::AnimNotify_StartShooting()
{
	UE_LOG(LogTemp, Warning, TEXT("RangedAI AnimNotify_StartShooting"));
}

void URangedAnimInstance::AnimNotify_StopShooting()
{
	UE_LOG(LogTemp, Warning, TEXT("RangedAI AnimNotify_StartShooting"));
}
