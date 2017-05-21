// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "EnemyAI/BountyHunter/BountyHunter.h"
#include "BountyHunterAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Engine.h"

void UBountyHunterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (GetWorld()->HasBegunPlay())
	{
		BountyHunter = Cast<ABountyHunter>(TryGetPawnOwner());
		//if (BountyHunter)
		//{
		//	if (BountyHunter->bIsInRange())
		//	{
		//		if (BountyHunter->GetEquippedWeapon()->CanFire())
		//		{
		//			if (bool t = BountyHunter->bCanTriggerRecoilAnimation())
		//			{
		//				bCanBasicAttack = t; //BountyHunter->GetEquippedWeapon()->Fire();
		//			}
		//			else
		//			{
		//				bCanBasicAttack = false;
		//			}
		//		}
		//		else if(AWeapon_Ranged* RecastWeapon = Cast<AWeapon_Ranged>(BountyHunter->GetEquippedWeapon()))
		//		{
		//			RecastWeapon->Reload();
		//		}
		//	}
			//CurrentEnemyState = BountyHunter->CurrentState;

			bIsAiming = BountyHunter->bIsAiming;
			//bCanBasicAttack = BountyHunter->bIsInRange();
			bCanBasicAttack = BountyHunter->GetEquippedWeapon()->CanFire();
			bIsBasicAttack = BountyHunter->bIsAttacking;
			bCanSetTrap = BountyHunter->bPlacingTrap;
			bIsDead = BountyHunter->Health <= 0.0f;
			bIsHardCC = BountyHunter->bIsInHardCC;
	}
}

void UBountyHunterAnimInstance::AnimNotify_StartShooting()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (bIsBasicAttack == true)
		{
			BountyHunter->CurrentlyEquippedWeapon->Fire();
		}
		BountyHunter->SetBountyHunterState(BountyHunterState::ATTACKING);
	}
}

void UBountyHunterAnimInstance::AnimNotify_EndShooting()
{
	BountyHunter->SetBountyHunterState(BountyHunterState::IDLE);
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

void UBountyHunterAnimInstance::AnimNotify_ReadyingAttack()
{

}

void UBountyHunterAnimInstance::AnimNotify_StartAiming()
{
	if (GetWorld()->HasBegunPlay())
	{
		BountyHunter->SetBountyHunterState(BountyHunterState::AIMING);
		bIsAiming = true;
	}
}

void UBountyHunterAnimInstance::AnimNotify_EndAiming()
{
	if (GetWorld()->HasBegunPlay())
	{
		bIsAiming = false;
		BountyHunter->bIsAttacking = true;
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