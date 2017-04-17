// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "EnemyAI/BountyHunter/BountyHunter.h"
#include "BountyHunterAnimInstance.h"

void UBountyHunterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	BountyHunter = Cast<ABountyHunter>(TryGetPawnOwner());

	if (BountyHunter)
	{
		bCanBasicAttack = BountyHunter->bIsInRange();
	}
}

void UBountyHunterAnimInstance::AnimNotify_BasicAttackShot()
{
	if (bCanBasicAttack)
	{
		// Functionality?
	}
}

void UBountyHunterAnimInstance::AnimNotify_PlaceTrap()
{
	if (bCanSetTrap)
	{
		// Functionality?
	}
}
