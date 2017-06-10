// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "EnemyAI/BountyHunter/BountyHunterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BountyHunterAnimInstance.h"
#include "Engine.h"

void UBountyHunterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	ALoneWolfCharacter* Owner = Cast<ALoneWolfCharacter>(TryGetPawnOwner());

	if (Owner != NULL)
	{
		Owner->OnDamageRecieved.AddDynamic(this, &ThisClass::OnDamageTaken);
	}
}

void UBountyHunterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (GetWorld()->HasBegunPlay())
	{
		Super::NativeUpdateAnimation(DeltaSeconds);
		BountyHunter = Cast<ABountyHunter>(TryGetPawnOwner());
		if (BountyHunter != NULL)
		{
			bIsDead = BountyHunter->Health <= 0.0f;
			bIsHardCC = BountyHunter->bIsInHardCC;
			bIsSettingTrap = BountyHunter->bIsPlacingTrap;
			CurrentBountyHunterState = BountyHunter->GetBountyHunterState();
		}
	}
}

void UBountyHunterAnimInstance::AnimNotify_ReturnToIdle()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (BountyHunter != NULL)
		{
			BountyHunter->bIsPlacingTrap = false;
			bIsSettingTrap = false;
			BountyHunter->SetBountyHunterState(BountyHunterState::IDLE);
		}
	}
}

void UBountyHunterAnimInstance::AnimNotify_Aiming()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (BountyHunter != NULL)
		{
			BountyHunter->bShouldAdjustGun = true;
		}
	}
}

void UBountyHunterAnimInstance::AnimNotify_StartShooting()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (BountyHunter != NULL)
		{
			if (BountyHunter->GetEquippedWeapon()->CanFire())
			{
				UE_LOG(LogTemp, Display, TEXT("ANIM//StartShooting"));
				BountyHunter->Attack();
			}
			else if (AWeapon_Ranged* RecastWeapon = Cast<AWeapon_Ranged>(BountyHunter->GetEquippedWeapon()))
			{
				RecastWeapon->Reload();
			}
		}
	}
}

void UBountyHunterAnimInstance::AnimNotify_EndShooting()
{
	if (GetWorld()->HasBegunPlay()) 
	{
		if (BountyHunter != NULL)
		{
			BountyHunter->SetBountyHunterState(BountyHunterState::IDLE);
			UE_LOG(LogTemp, Display, TEXT("ANIM//EndShooting"));
			BountyHunter->bShouldAdjustGun = false;
		}
	}
}

void UBountyHunterAnimInstance::AnimNotify_PlaceTrap()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (BountyHunter != NULL)
		{
			BountyHunter->bIsPlacingTrap = false;
		}
	}
}
