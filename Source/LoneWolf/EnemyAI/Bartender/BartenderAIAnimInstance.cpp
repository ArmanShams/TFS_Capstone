// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BartenderAIAnimInstance.h"
#include "BartenderAI.h"

void UBartenderAIAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (GetWorld()->HasBegunPlay())
	{
		Bartender = Cast<ABartenderAI>(TryGetPawnOwner());

		if (Bartender != NULL)
		{
			bIsAttacking = Bartender->GetIsAttacking();
		}
	}
}

void UBartenderAIAnimInstance::AnimNotify_SpawnMolotov()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (Bartender != NULL)
		{
			Bartender->ThrowMolotov();
		}
	}
}

void UBartenderAIAnimInstance::AnimNotify_EndAttack()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (Bartender != NULL)
		{
			Bartender->SetIsAttacking(false);
		}
	}
}
