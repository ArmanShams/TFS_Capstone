// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "EnemyAI/BountyHunter/BountyHunterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BountyHunterAnimInstance.h"
#include "Engine.h"

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
			bIsSettingTrap = BountyHunter->bIsSetTrap;
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
			BountyHunter->bShouldAdjustGun = false;
		}
	}
}

void UBountyHunterAnimInstance::AnimNotify_SpawnTrap()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (BountyHunter != NULL)
		{
		}
	}
}

void UBountyHunterAnimInstance::AnimNotify_PlaceTrap()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (BountyHunter != NULL)
		{
		}
	}
}

void UBountyHunterAnimInstance::AnimNotify_StartStunned()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (BountyHunter != NULL)
		{
			bIsHardCC = true;
			if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(TryGetPawnOwner()->GetController())->GetBrainComponent()->GetBlackboardComponent())
			{
				BlackboardComponent->SetValueAsBool(TEXT("bIsHardCC"), true);
			}
		}
	}
}

void UBountyHunterAnimInstance::AnimNotify_EndStunned()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (BountyHunter != NULL)
		{
			bIsHardCC = false;
			if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(TryGetPawnOwner()->GetController())->GetBrainComponent()->GetBlackboardComponent())
			{
				BlackboardComponent->SetValueAsBool(TEXT("bIsHardCC"), false);
			}
		}
	}
}

void UBountyHunterAnimInstance::AnimNotify_FootstepEvent()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (BountyHunter != NULL)
		{
		}
	}
}
