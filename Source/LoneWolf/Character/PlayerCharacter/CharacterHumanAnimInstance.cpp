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
			if (!bPrimaryFire)
			{
				bPrimaryFire = CharacterController->bAnimPrimaryFire;
			}
			
			bSecondaryFiring = CharacterController->bAnimSecondaryFire;
			bIsDead = CharacterController->Health <= 0.f;
			bReloading = CharacterController->bShouldEnterReload;
			bIsInHardCC = CharacterController->bIsInHardCC;
			bIsInSoftCC = CharacterController->bIsInSoftCC;
			CurrentForm = CharacterController->CurrentForm;
			AnimMovementSpeed = CharacterController->AnimMovementSpeed * 600.f;
			AnimMovementDirection = CharacterController->AnimMovementDirection * 150.f;
			AimOffsetYaw = CharacterController->AimOffsetYaw;
			switch (CharacterController->GetRelativeFacing())
			{
			case EightDirectional::NONE:

				break;
			case EightDirectional::RIGHT:
				if (CharacterController->GetRelativeMovement() == EightDirectional::LEFT)
				{
					ForwardMovementMultiplier = -1;
				}
				break;
			case EightDirectional::DOWN_RIGHT:
				break;
			case EightDirectional::DOWN:
				break;
			case EightDirectional::DOWN_LEFT:
				break;
			case EightDirectional::LEFT:
				break;
			case EightDirectional::UP_LEFT:
				break;
			case EightDirectional::UP:
				break;
			case EightDirectional::UP_RIGHT:
				break;
			default:
				break;
			}

			if (bPrimaryFire)
			{
				CharacterController->bAnimPrimaryFire = bPrimaryFire;
			}
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
			bPrimaryFire = false;
			CharacterController->bAnimPrimaryFire = bPrimaryFire;
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
			CharacterController->RollDirection = FVector::ZeroVector;
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

void UCharacterHumanAnimInstance::AnimNotify_DisableInputAndMakeInvulnerable()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (CharacterController != NULL)
		{
			CharacterController->RevokeControlAndBecomeInvulnerable();
		}
	}
}

void UCharacterHumanAnimInstance::AnimNotify_EnableInputAndRevokeInvulnerable()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (CharacterController != NULL)
		{
			CharacterController->RestoreControlAndRevokeInvulnerable();
		}
	}
}

void UCharacterHumanAnimInstance::AnimNotify_ReplaceMesh()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (CharacterController != NULL)
		{
			CharacterController->TransformIntoWolf();
		}
	}
}

void UCharacterHumanAnimInstance::RecenterMeshOnCursor()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (CharacterController != NULL)
		{
			CharacterController->bRecenterMesh = true;
		}
	}
}
