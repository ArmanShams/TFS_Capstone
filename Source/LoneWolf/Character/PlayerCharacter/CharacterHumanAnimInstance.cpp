// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "CharacterHumanAnimInstance.h"
#include "Character/PlayerCharacter/CharacterController.h"
#include "Weapons/Weapon.h"
#include "Weapons/Weapon_Melee.h"
#include "Weapons/Weapon_Ranged.h"

void UCharacterHumanAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (GetWorld()->HasBegunPlay())
	{
		CharacterController = Cast<ACharacterController>(TryGetPawnOwner());

		if (CharacterController != NULL)
		{
			//if (CharacterController->CurrentForm == TransformationState::HUMAN)
			{
				bRolling = CharacterController->bIsRolling;
				
				bPrimaryFire = CharacterController->bAnimPrimaryFire;
				
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

				if (!CharacterController->bIsInSoftCC)
				{
					switch (CharacterFacing)
					{
					case EightDirectional::NONE:
						break;
					case EightDirectional::RIGHT:
						switch (CharacterMovement)
						{
						case EightDirectional::NONE:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = 0;
							break;
						case EightDirectional::RIGHT:
							ForwardMovementMultiplier = 1;
							RightMovementMultiplier = 0;
							break;
						case EightDirectional::DOWN_RIGHT:
							ForwardMovementMultiplier = 1;
							RightMovementMultiplier = 1;
							break;
						case EightDirectional::DOWN:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = 1;
							break;
						case EightDirectional::DOWN_LEFT:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = 1;
							break;
						case EightDirectional::LEFT:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = 0;
							break;
						case EightDirectional::UP_LEFT:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = -1;
							break;
						case EightDirectional::UP:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = -1;
							break;
						case EightDirectional::UP_RIGHT:
							ForwardMovementMultiplier = 1;
							RightMovementMultiplier = -1;
							break;
						default:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = 0;
							break;
						}
						break;
					case EightDirectional::DOWN_RIGHT:
						switch (CharacterMovement)
						{
						case EightDirectional::NONE:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = 0;
							break;
						case EightDirectional::RIGHT:
							ForwardMovementMultiplier = 1;
							RightMovementMultiplier = -1;
							break;
						case EightDirectional::DOWN_RIGHT:
							ForwardMovementMultiplier = 1;
							RightMovementMultiplier = 0;
							break;
						case EightDirectional::DOWN:
							ForwardMovementMultiplier = 1;
							RightMovementMultiplier = 1;
							break;
						case EightDirectional::DOWN_LEFT:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = 1;
							break;
						case EightDirectional::LEFT:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = 1;
							break;
						case EightDirectional::UP_LEFT:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = 0;
							break;
						case EightDirectional::UP:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = -1;
							break;
						case EightDirectional::UP_RIGHT:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = -1;
							break;
						default:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = 0;
							break;
						}
						break;
					case EightDirectional::DOWN:
						switch (CharacterMovement)
						{
						case EightDirectional::NONE:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = 0;
							break;
						case EightDirectional::RIGHT:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = -1;
							break;
						case EightDirectional::DOWN_RIGHT:
							ForwardMovementMultiplier = 1;
							RightMovementMultiplier = -1;
							break;
						case EightDirectional::DOWN:
							ForwardMovementMultiplier = 1;
							RightMovementMultiplier = 0;
							break;
						case EightDirectional::DOWN_LEFT:
							ForwardMovementMultiplier = 1;
							RightMovementMultiplier = 1;
							break;
						case EightDirectional::LEFT:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = 1;
							break;
						case EightDirectional::UP_LEFT:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = 1;
							break;
						case EightDirectional::UP:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = 0;
							break;
						case EightDirectional::UP_RIGHT:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = -1;
							break;
						default:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = 0;
							break;
						}
						break;
					case EightDirectional::DOWN_LEFT:
						switch (CharacterMovement)
						{
						case EightDirectional::NONE:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = 0;
							break;
						case EightDirectional::RIGHT:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = -1;
							break;
						case EightDirectional::DOWN_RIGHT:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = -1;
							break;
						case EightDirectional::DOWN:
							ForwardMovementMultiplier = 1;
							RightMovementMultiplier = -1;
							break;
						case EightDirectional::DOWN_LEFT:
							ForwardMovementMultiplier = 1;
							RightMovementMultiplier = 0;
							break;
						case EightDirectional::LEFT:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = 1;
							break;
						case EightDirectional::UP_LEFT:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = -1;
							break;
						case EightDirectional::UP:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = 1;
							break;
						case EightDirectional::UP_RIGHT:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = 0;
							break;
						default:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = 0;
							break;
						}
						break;
					case EightDirectional::LEFT:
						switch (CharacterMovement)
						{
						case EightDirectional::NONE:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = 0;
							break;
						case EightDirectional::RIGHT:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = 0;
							break;
						case EightDirectional::DOWN_RIGHT:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = -1;
							break;
						case EightDirectional::DOWN:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = -1;
							break;
						case EightDirectional::DOWN_LEFT:
							ForwardMovementMultiplier = 1;
							RightMovementMultiplier = -1;
							break;
						case EightDirectional::LEFT:
							ForwardMovementMultiplier = 1;
							RightMovementMultiplier = 0;
							break;
						case EightDirectional::UP_LEFT:
							ForwardMovementMultiplier = 1;
							RightMovementMultiplier = 1;
							break;
						case EightDirectional::UP:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = 1;
							break;
						case EightDirectional::UP_RIGHT:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = 1;
							break;
						default:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = 0;
							break;
						}
						break;
					case EightDirectional::UP_LEFT:
						switch (CharacterMovement)
						{
						case EightDirectional::NONE:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = 0;
							break;
						case EightDirectional::RIGHT:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = 1;
							break;
						case EightDirectional::DOWN_RIGHT:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = 0;
							break;
						case EightDirectional::DOWN:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = -1;
							break;
						case EightDirectional::DOWN_LEFT:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = -1;
							break;
						case EightDirectional::LEFT:
							ForwardMovementMultiplier = 1;
							RightMovementMultiplier = -1;
							break;
						case EightDirectional::UP_LEFT:
							ForwardMovementMultiplier = 1;
							RightMovementMultiplier = 0;
							break;
						case EightDirectional::UP:
							ForwardMovementMultiplier = 1;
							RightMovementMultiplier = 1;
							break;
						case EightDirectional::UP_RIGHT:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = 1;
							break;
						default:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = 0;
							break;
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
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = 1;
							break;
						case EightDirectional::DOWN_RIGHT:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = 1;
							break;
						case EightDirectional::DOWN:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = 0;
							break;
						case EightDirectional::DOWN_LEFT:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = -1;
							break;
						case EightDirectional::LEFT:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = -1;
							break;
						case EightDirectional::UP_LEFT:
							ForwardMovementMultiplier = 1;
							RightMovementMultiplier = -1;
							break;
						case EightDirectional::UP:
							ForwardMovementMultiplier = 1;
							RightMovementMultiplier = 0;
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
						switch (CharacterMovement)
						{
						case EightDirectional::NONE:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = 0;
							break;
						case EightDirectional::RIGHT:
							ForwardMovementMultiplier = 1;
							RightMovementMultiplier = 1;
							break;
						case EightDirectional::DOWN_RIGHT:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = 1;
							break;
						case EightDirectional::DOWN:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = 1;
							break;
						case EightDirectional::DOWN_LEFT:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = 0;
							break;
						case EightDirectional::LEFT:
							ForwardMovementMultiplier = -1;
							RightMovementMultiplier = -1;
							break;
						case EightDirectional::UP_LEFT:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = -1;
							break;
						case EightDirectional::UP:
							ForwardMovementMultiplier = 1;
							RightMovementMultiplier = -1;
							break;
						case EightDirectional::UP_RIGHT:
							ForwardMovementMultiplier = 1;
							RightMovementMultiplier = 0;
							break;
						default:
							ForwardMovementMultiplier = 0;
							RightMovementMultiplier = 0;
							break;
						}
						break;
					default:
						ForwardMovementMultiplier = 0;
						RightMovementMultiplier = 0;
						break;
					}
				}
				else
				{
					ForwardMovementMultiplier = 0;
					RightMovementMultiplier = 0;
				}
			
				AnimMovementSpeed = CharacterController->AnimMovementSpeed;
				AnimMovementDirection = CharacterController->AnimMovementDirection;
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
			bSecondaryFiring = false;
			CharacterController->SetAnimPrimaryFire(false);
			CharacterController->SetAnimSecondaryFire(false);
			CharacterController->SetShouldReload(false);
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
			CharacterController->GetController()->StopMovement();
			CharacterController->InstantOrientToCursor();
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
			bSecondaryFiring = false;
			CharacterController->SetAnimPrimaryFire(false);
			CharacterController->SetAnimSecondaryFire(false);
		}
	}
}

void UCharacterHumanAnimInstance::AnimNotify_DespawnWeapon()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (CharacterController != NULL)
		{
			CharacterController->DespawnCurrentWeapon();
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

			CharacterController->RestoreControlAndRevokeInvulnerable();

			CharacterController = NULL;
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

void UCharacterHumanAnimInstance::OrientMeshToMovement()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (CharacterController != NULL)
		{
			CharacterController->OrientMeshToMovementDirection();
		}
	}
}

void UCharacterHumanAnimInstance::ForceCompletionOfReload()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (CharacterController != NULL)
		{
			bReloading = false;
			bPrimaryFire = false;
			bSecondaryFiring = false;
			CharacterController->SetAnimPrimaryFire(false);
			CharacterController->SetAnimSecondaryFire(false);
			CharacterController->SetShouldReload(false);
			CharacterController->Reload();
		}
	}
}

void UCharacterHumanAnimInstance::EnsureFiringTransition()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (CharacterController != NULL)
		{
			bPrimaryFire = false;
			bSecondaryFiring = false;
			CharacterController->SetAnimPrimaryFire(false);
			CharacterController->SetAnimSecondaryFire(false);
		}
	}
}
