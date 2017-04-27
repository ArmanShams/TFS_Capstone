// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "SheriffAnimInstance.h"

void USheriffAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (SheriffAI)
	{
		bCanBasicAttack = SheriffAI->bIsInRange();
	}
}

void USheriffAnimInstance::AnimNotify_BasicAttackShot()
{

}

void USheriffAnimInstance::AnimNotify_LassoAttack()
{

}
