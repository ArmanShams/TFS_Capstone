// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BartenderAIAnimInstance.h"
#include "BartenderAI.h"

void UBartenderAIAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	ALoneWolfCharacter* Owner = Cast<ALoneWolfCharacter>(TryGetPawnOwner());

	if (Owner != NULL)
	{
		Owner->OnDamageRecieved.AddDynamic(this, &ThisClass::OnDamageTaken);
	}
}

void UBartenderAIAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (GetWorld()->HasBegunPlay())
	{
		Bartender = Cast<ABartenderAI>(TryGetPawnOwner());

		if (Bartender != NULL)
		{
			bIsAttacking = Bartender->GetIsAttacking();
			bIsDead = Bartender->Health <= 0.0f;
			bIsInHardCC = Bartender->bIsInHardCC;
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
