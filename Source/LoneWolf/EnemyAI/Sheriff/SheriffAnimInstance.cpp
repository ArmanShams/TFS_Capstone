// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "SheriffAnimInstance.h"

void USheriffAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	
}

void USheriffAnimInstance::AnimNotify_ShootRevolver()
{
	if (GetWorld()->HasBegunPlay())
	{

	}

	if (SheriffAI)
	{
		RevolverRange = SheriffAI->RevolverAttackRange;
		bKnifeSwing = SheriffAI->bIsInRange(RevolverRange);
	}
}

void USheriffAnimInstance::AnimNotify_LassoAttack()
{
	if (SheriffAI)
	{
		LassoRange = SheriffAI->RevolverAttackRange;
		bShootRevolver = SheriffAI->bIsInRange(LassoRange);
	}
}
