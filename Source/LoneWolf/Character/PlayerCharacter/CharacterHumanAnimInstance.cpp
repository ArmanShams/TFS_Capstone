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
			ForwardMovementMultiplier = 0;
			bSecondaryFiring = CharacterController->bAnimSecondaryFire;
			bIsDead = CharacterController->Health <= 0.f;
			bReloading = CharacterController->bShouldEnterReload;
			bIsInHardCC = CharacterController->bIsInHardCC;
			bIsInSoftCC = CharacterController->bIsInSoftCC;
			CurrentForm = CharacterController->CurrentForm;		
			AimOffsetYaw = CharacterController->AimOffsetYaw;

			EightDirectional CharacterFacing = CharacterController->GetRelativeFacing();
			EightDirectional CharacterMovement = CharacterController->GetRelativeMovement();

			switch (CharacterFacing)
			{
			case EightDirectional::NONE:
				break;
			case EightDirectional::RIGHT:
				if (CharacterMovement == EightDirectional::LEFT)
				{
					ForwardMovementMultiplier = -1;
				}
				if (CharacterMovement == EightDirectional::RIGHT)
				{
					ForwardMovementMultiplier = 1;
				}
				break;
			case EightDirectional::DOWN_RIGHT:
				if (CharacterMovement == EightDirectional::UP_LEFT)
				{
					ForwardMovementMultiplier = -1;
				}
				if (CharacterMovement == EightDirectional::DOWN_RIGHT)
				{
					ForwardMovementMultiplier = 1;
				}
				break;
			case EightDirectional::DOWN:
				if (CharacterMovement == EightDirectional::UP)
				{
					ForwardMovementMultiplier = -1;
				}
				if (CharacterMovement == EightDirectional::DOWN)
				{
					ForwardMovementMultiplier = 1;
				}
				break;
			case EightDirectional::DOWN_LEFT:
				if (CharacterMovement == EightDirectional::UP_RIGHT)
				{
					ForwardMovementMultiplier = -1;
				}
				if (CharacterMovement == EightDirectional::DOWN_LEFT)
				{
					ForwardMovementMultiplier = 1;
				}
				break;
			case EightDirectional::LEFT:
				if (CharacterMovement == EightDirectional::RIGHT)
				{
					ForwardMovementMultiplier = -1;
				}
				if (CharacterMovement == EightDirectional::LEFT)
				{
					ForwardMovementMultiplier = 1;
				}
				break;
			case EightDirectional::UP_LEFT:
				if (CharacterMovement == EightDirectional::DOWN_RIGHT)
				{
					ForwardMovementMultiplier = -1;
				}
				if (CharacterMovement == EightDirectional::UP_LEFT)
				{
					ForwardMovementMultiplier = 1;
				}
				break;
			case EightDirectional::UP:
				switch (CharacterMovement)
				{
				case EightDirectional::NONE:
					ForwardMovementMultiplier = 0;
					RightMovementMultiplier = 0;
					break;
				case EightDirectional::RIGHT:
					RightMovementMultiplier = 1;
					break;
				case EightDirectional::DOWN_RIGHT:
					RightMovementMultiplier = -1;
					ForwardMovementMultiplier = -1;
					break;
				case EightDirectional::DOWN:
					ForwardMovementMultiplier = -1;
					break;
				case EightDirectional::DOWN_LEFT:
					RightMovementMultiplier = 1;
					ForwardMovementMultiplier = -1;
					break;
				case EightDirectional::LEFT:
					RightMovementMultiplier = -1;
					break;
				case EightDirectional::UP_LEFT:
					ForwardMovementMultiplier = 1;
					RightMovementMultiplier = -1;
					break;
				case EightDirectional::UP:
					ForwardMovementMultiplier = 1;
					break;
				case EightDirectional::UP_RIGHT:
					ForwardMovementMultiplier = 1;
					RightMovementMultiplier = 1;
					break;
				default:
					ForwardMovementMultiplier = 0;
					RightMovementMultiplier = 0;
					break;
				}
				break;
			case EightDirectional::UP_RIGHT:
				if (CharacterMovement == EightDirectional::DOWN_LEFT)
				{
					ForwardMovementMultiplier = -1;
				}
				if (CharacterMovement == EightDirectional::UP_RIGHT)
				{
					ForwardMovementMultiplier = 1;
				}
				break;
			default:
				break;
			}
			AnimMovementSpeed = CharacterController->AnimMovementSpeed;
			AnimMovementDirection = CharacterController->AnimMovementDirection;


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
