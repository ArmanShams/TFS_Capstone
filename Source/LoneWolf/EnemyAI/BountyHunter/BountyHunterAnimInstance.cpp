// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "EnemyAI/BountyHunter/BountyHunter.h"
#include "BountyHunterAnimInstance.h"

void UBountyHunterAnimInstance::NativeInitializeAnimation()
{

}

void UBountyHunterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (GetWorld()->HasBegunPlay())
	{
		BountyHunterClass = Cast<ABountyHunter>(TryGetPawnOwner());

		if (BountyHunterClass)
		{
			//CurrentBountyHunterState = BountyHunterClass->CurrentState;

			if (BountyHunterClass->bIsInRange())
			{
				if (BountyHunterClass->GetEquippedWeapon()->CanFire())
				{
					if (bool t = BountyHunterClass->bCanTriggerRecoilAnimation())
					{
						bCanBasicAttack = t;
					}
					else
					{
						bCanBasicAttack = false;
					}
				}
				else if(AWeapon_Ranged* RecastWeapon = Cast<AWeapon_Ranged>(BountyHunterClass->GetEquippedWeapon()))
				{
					RecastWeapon->Reload();
				}
			}
		}	
	}
}

void UBountyHunterAnimInstance::AnimNotify_Shoot()
{
	if (GetWorld()->HasBegunPlay())
	{
		BountyHunterClass->GetEquippedWeapon()->Fire();
		BountyHunterClass->SetBountyHunterState(BountyHunterState::IDLE);
	}
}

void UBountyHunterAnimInstance::AnimNotify_PlaceTrap()
{
	if (GetWorld()->HasBegunPlay())
	{
		//BountyHunter->SetBearTrap();
	}
}
