// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "SheriffAnimInstance.h"

void USheriffAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (SheriffAI)
	{
		bKnifeSwing = SheriffAI->bIsInRange();
	}
}

void USheriffAnimInstance::AnimNotify_KnifeSwing()
{
	if (SheriffAI)
	{
		KnifeRange = SheriffAI->RevolverAttackRange;
		bShootRevolver = SheriffAI->bIsInRange(KnifeRange);
	}
}

void USheriffAnimInstance::AnimNotify_ShootRevolver()
{
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
