// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "CharacterHumanAnimInstance.h"
#include "Character/PlayerCharacter/CharacterController.h"
#include "Weapons/Weapon.h"
#include "Weapons/Weapon_Melee.h"
#include "Weapons/Weapon_Ranged.h"

void UCharacterHumanAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (GetWorld()->HasBegunPlay())
	{
		Super::NativeUpdateAnimation(DeltaSeconds);

		CharacterController = Cast<ACharacterController>(TryGetPawnOwner());

		if (CharacterController != NULL)
		{
			bRolling = CharacterController->bIsRolling;
			bPrimaryFire = CharacterController->bAnimPrimaryFire;
			bSecondaryFiring = CharacterController->bAnimSecondaryFire;
			bIsDead = CharacterController->Health <= 0.f;
			bReloading = CharacterController->bShouldEnterReload;
			bIsInHardCC = CharacterController->bIsInHardCC;
			bIsInSoftCC = CharacterController->bIsInSoftCC;
		}
	}
}

void UCharacterHumanAnimInstance::AnimNotify_Reload()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (CharacterController != NULL)
		{
			CharacterController->Reload();
		}
	}
}

void UCharacterHumanAnimInstance::AnimNotify_ReloadEnd()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (CharacterController != NULL)
		{
			bReloading = false;
			CharacterController->bShouldEnterReload = bReloading;
		}
	}
}

void UCharacterHumanAnimInstance::AnimNotify_ToggleRollState()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (CharacterController != NULL)
		{
			CharacterController->bIsRolling = !CharacterController->bIsRolling;
			UE_LOG(LogTemp, Display, TEXT("Ending Roll"));
		}
	}
}

void UCharacterHumanAnimInstance::AnimNotify_EndPrimaryFire()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (CharacterController != NULL)
		{
			bPrimaryFire = false;
			CharacterController->bAnimPrimaryFire = bPrimaryFire;
		}
	}

}
