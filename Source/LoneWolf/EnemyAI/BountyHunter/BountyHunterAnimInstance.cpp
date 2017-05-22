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
			bIsBasicAttack = BountyHunter->bIsBasicAttack;
			bIsAiming = BountyHunter->bIsAiming;
			bCanSetTrap = BountyHunter->bPlacingTrap;
		}
	}
}

void UBountyHunterAnimInstance::AnimNotify_StartShooting()
{ UE_LOG(LogTemp, Display, TEXT("BountyHunterAnim//StartShooting"));
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
{ UE_LOG(LogTemp, Display, TEXT("BountyHunterAnim//EndShooting"));
	
	bIsAiming = false;
	BountyHunter->SetBountyHunterState(BountyHunterState::IDLE);
}

void UBountyHunterAnimInstance::AnimNotify_SpawnTrap()
{ UE_LOG(LogTemp, Display, TEXT("BountyHunterAnim//SpawnTrap"));
	BountyHunter->SetBountyHunterState(BountyHunterState::SETTINGTRAP);
}

void UBountyHunterAnimInstance::AnimNotify_PlaceTrap()
{ UE_LOG(LogTemp, Display, TEXT("BountyHunterAnim//EndPlaceTrap"));
	if (GetWorld()->HasBegunPlay())
	{
		BountyHunter->bPlacingTrap = false;
	}
}

void UBountyHunterAnimInstance::AnimNotify_ReadyingAttack()
{ UE_LOG(LogTemp, Display, TEXT("BountyHunterAnim//ReadyingAttack"));
}

void UBountyHunterAnimInstance::AnimNotify_StartAiming()
{
	if (GetWorld()->HasBegunPlay())
	{ UE_LOG(LogTemp, Display, TEXT("BountyHunterAnim//StartAiming"));
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("Aim Start!")));

	}
}

void UBountyHunterAnimInstance::AnimNotify_EndAiming()
{
	if (GetWorld()->HasBegunPlay())
	{ UE_LOG(LogTemp, Display, TEXT("BountyHunterAnim//EndAiming"));
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("Aim End!")));
		//BountyHunter->bIsAttacking = true;
		BountyHunter->SetBountyHunterState(BountyHunterState::ATTACKING);
	}
}

void UBountyHunterAnimInstance::AnimNotify_ReturnToIdle()
{ UE_LOG(LogTemp, Display, TEXT("BountyHunterAnim//ReturnToIdle"));
	if (GetWorld()->HasBegunPlay())
	{
		if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(TryGetPawnOwner()->GetController())->GetBrainComponent()->GetBlackboardComponent())
		{
			BlackboardComponent->SetValueAsBool(TEXT("bIsIdle"), true);
		}
	}
}

void UBountyHunterAnimInstance::AnimNotify_StartStunned()
{ UE_LOG(LogTemp, Display, TEXT("BountyHunterAnim//StartStunned"));
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
{ UE_LOG(LogTemp, Display, TEXT("BountyHunterAnim//EndStunne ,d"));
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