// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "EnemyAI/RangedAI.h"
#include "RangedAnimInstance.h"

void URangedAnimInstance::NativeUpdateAnimation(float DeltaSeconds) 
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	{
		//	TryGetPawnOwner: Targets the AnimInstance Reference and returns the value of pawn reference 

		ARangedAI* RangedAI = Cast<ARangedAI>(TryGetPawnOwner());

		if (RangedAI)
		{
			bIsShooting = RangedAI->Aim();
		}
	}
}

void URangedAnimInstance::AnimNotify_StartShooting()
{
	bIsShooting = true;
}

void URangedAnimInstance::AnimNotify_StopShooting()
{
	bIsShooting = false;
}
