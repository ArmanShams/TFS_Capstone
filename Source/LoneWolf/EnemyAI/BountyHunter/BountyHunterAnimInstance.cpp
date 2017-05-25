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
			CurrentBountyHunterState = BountyHunter->GetBountyHunterState();
			bCanBasicAttack = BountyHunter->GetEquippedWeapon()->CanFire();
			bIsBasicAttack = BountyHunter->bIsAttacking;
			bIsAiming = BountyHunter->bIsAiming;
			bCanSetTrap = BountyHunter->bPlacingTrap;
		}
	}
}

void UBountyHunterAnimInstance::AnimNotify_ReturnToIdle()
{
	BountyHunter->SetBountyHunterState(BountyHunterState::IDLE);	
}

void UBountyHunterAnimInstance::AnimNotify_Aiming()
{
	if (GetWorld()->HasBegunPlay())
	{
		BountyHunter->bIsAiming = true;
	}
}

void UBountyHunterAnimInstance::AnimNotify_StartShooting()
{
	if (GetWorld()->HasBegunPlay())
	{
		BountyHunter->Attack();
		BountyHunter->CurrentlyEquippedWeapon->Fire();
		//BountyHunter->bIsAttacking = true;
		bIsBasicAttack = true;
	}
}

void UBountyHunterAnimInstance::AnimNotify_EndShooting()
{
	if (GetWorld()->HasBegunPlay()) 
	{
		BountyHunter->bIsAttacking = false; 
		bIsBasicAttack = false;
	}
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
