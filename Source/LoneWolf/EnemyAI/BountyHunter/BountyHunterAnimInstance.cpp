// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "EnemyAI/BountyHunter/BountyHunter.h"
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
			bCanBasicAttack = BountyHunter->GetEquippedWeapon()->CanFire();
			bIsBasicAttack = BountyHunter->bIsAttacking;
			bIsAiming = BountyHunter->bIsAiming;
			bCanSetTrap = BountyHunter->bPlacingTrap;
		}
	}
}

void UBountyHunterAnimInstance::AnimNotify_StartShooting()
{ //UE_LOG(LogTemp, Display, TEXT("BountyHunterAnim//StartShooting"));
	if (GetWorld()->HasBegunPlay())
	{
		if (bIsBasicAttack == true)
		{
			if (!bCanBasicAttack)
			{
				AWeapon_Ranged* RecastWeapon = Cast<AWeapon_Ranged>(BountyHunter->GetEquippedWeapon());
				RecastWeapon->Reload();
			}
			BountyHunter->CurrentlyEquippedWeapon->Fire();
		}
	}
}

void UBountyHunterAnimInstance::AnimNotify_EndShooting()
{ 
	bIsAiming = false;
	BountyHunter->bIsAttacking = false;
}

void UBountyHunterAnimInstance::AnimNotify_SpawnTrap()
{
	BountyHunter->SetBountyHunterState(BountyHunterState::SETTINGTRAP);
}

void UBountyHunterAnimInstance::AnimNotify_PlaceTrap()
{
	if (GetWorld()->HasBegunPlay())
	{
		BountyHunter->bPlacingTrap = false;
	}
}

void UBountyHunterAnimInstance::AnimNotify_StartAiming()
{
	if (GetWorld()->HasBegunPlay())
	{
	  BountyHunter->SetBountyHunterState(BountyHunterState::AIMING);
	}
}

void UBountyHunterAnimInstance::AnimNotify_ReturnToIdle()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(TryGetPawnOwner()->GetController())->GetBrainComponent()->GetBlackboardComponent())
		{
			BlackboardComponent->SetValueAsBool(TEXT("bIsIdle"), true);
		}
	}
}

void UBountyHunterAnimInstance::AnimNotify_StartStunned()
{
	if (GetWorld()->HasBegunPlay())
	{
		bIsHardCC = true;
		if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(TryGetPawnOwner()->GetController())->GetBrainComponent()->GetBlackboardComponent())
		{
			BlackboardComponent->SetValueAsBool(TEXT("bIsHardCC"), true);
		}
	}
}

void UBountyHunterAnimInstance::AnimNotify_EndStunned()
{
	if (GetWorld()->HasBegunPlay())
	{
		bIsHardCC = false;
		if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(TryGetPawnOwner()->GetController())->GetBrainComponent()->GetBlackboardComponent())
		{
			BlackboardComponent->SetValueAsBool(TEXT("bIsHardCC"), false);
		}
	}
}

void UBountyHunterAnimInstance::AnimNotify_FootstepEvent()
{
}