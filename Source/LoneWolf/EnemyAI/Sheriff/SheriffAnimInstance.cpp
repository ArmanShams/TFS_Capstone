// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "EnemyAI/Sheriff/SheriffAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Engine.h"
#include "SheriffAnimInstance.h"

void USheriffAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (GetWorld()->HasBegunPlay())
	{
		Super::NativeUpdateAnimation(DeltaSeconds);
		Sheriff = Cast<ASheriffAI>(TryGetPawnOwner());
		{
			bIsDead = Sheriff->Health <= 0.0f;
			bIsHardCC = Sheriff->bIsInHardCC;
			CurrentSheriffSate = Sheriff->GetSheriffState();
		}
	}
}

void USheriffAnimInstance::AnimNotify_Lasso()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (Sheriff != NULL)
		{
			//Lasso casted and hit enemy
		}
	}
}

void USheriffAnimInstance::AnimNotify_EndPull()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (Sheriff != NULL)
		{
			//Sheriff tugging on enemy
		}
	}
}

void USheriffAnimInstance::AnimNotify_FirstShot()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (Sheriff != NULL)
		{
			//First Shot in the attacking state
		}
	}
}

void USheriffAnimInstance::AnimNotify_SecondShot()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (Sheriff != NULL)
		{
			//Second Shot in the attacking state
		}
	}
}

void USheriffAnimInstance::AnimNotify_EndReload()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (Sheriff != NULL)
		{
			//Reloading shotgun
		}
	}
}