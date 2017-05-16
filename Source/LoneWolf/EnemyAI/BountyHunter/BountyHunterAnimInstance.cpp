// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "EnemyAI/BountyHunter/BountyHunter.h"
#include "BountyHunterAnimInstance.h"

void UBountyHunterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (GetWorld()->HasBegunPlay())
	{
		BountyHunter = Cast<ABountyHunter>(TryGetPawnOwner());

		if (BountyHunter)
		{
			if (BountyHunter->bIsInRange())
			{
				if (BountyHunter->GetEquippedWeapon()->CanFire())
				{
					if (bool t = BountyHunter->bCanTriggerRecoilAnimation())
					{
						bCanBasicAttack = t;
					}
					else
					{
						bCanBasicAttack = false;
					}
				}
				else if(AWeapon_Ranged* RecastWeapon = Cast<AWeapon_Ranged>(BountyHunter->GetEquippedWeapon()))
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
		BountyHunter->SetBountyHunterState(BounterHunterState::ATTACKING);
		BountyHunter->Attack();
	}
}

void UBountyHunterAnimInstance::AnimNotify_PlaceTrap()
{
	if (GetWorld()->HasBegunPlay())
	{
		BountyHunter->SetBountyHunterState(BounterHunterState::SETTINGTRAP);
	}
}
