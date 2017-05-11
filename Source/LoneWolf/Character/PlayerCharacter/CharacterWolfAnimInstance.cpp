// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "CharacterWolfAnimInstance.h"
#include "Character/PlayerCharacter/CharacterController.h"
#include "Weapons/Weapon.h"
#include "Weapons/Weapon_Melee.h"
#include "Weapons/Weapon_Ranged.h"


void UCharacterWolfAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (GetWorld()->HasBegunPlay())
	{
		Super::NativeUpdateAnimation(DeltaSeconds);

		CharacterController = Cast<ACharacterController>(TryGetPawnOwner());

		if (CharacterController != NULL)
		{
			bRolling = CharacterController->bIsRolling;
			//if (!bPrimaryFire)
			{
				//bPrimaryFire = CharacterController->bAnimPrimaryFire;
			}
			bCanAttack = CharacterController->IsMeleeAttacking();
			//bSecondaryFiring = CharacterController->bAnimSecondaryFire;
			bIsDead = CharacterController->Health <= 0.f;
			//bReloading = CharacterController->bShouldEnterReload;
			bIsInHardCC = CharacterController->bIsInHardCC;
			bIsInSoftCC = CharacterController->bIsInSoftCC;
			CurrentForm = CharacterController->CurrentForm;
			CurrentMeleeAttackType = CharacterController->CurrentMeleeAttackType;
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

			switch (CurrentMeleeAttackType)
			{
			case UAttackTypes::NONE:
				AttackType = AttackTypeWrapper::NONE;
				break;
			case UAttackTypes::SWIFT:
				break;
			case UAttackTypes::LIGHT:
				AttackType = AttackTypeWrapper::LIGHT;
				break;
			case UAttackTypes::HEAVY:
				AttackType = AttackTypeWrapper::HEAVY;
				break;
			default:
				AttackType = AttackTypeWrapper::NONE;
				break;
			}
		}
	}
}

void UCharacterWolfAnimInstance::AnimNotify_MeleeAtkStart()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (AWeapon_Melee* RecastWeapon = Cast<AWeapon_Melee>(CharacterController->CurrentlyEquippedWeapon))
		{
			if (bCanAttack)
			{
				//UE_LOG(LogTemp, Display, TEXT("We are in the beam"));
				RecastWeapon->ToggleCollider();
				RecastWeapon->SetAttackType(CurrentMeleeAttackType);
			}
			if (bRolling)
			{
				RecastWeapon->ToggleCollider();
				RecastWeapon->SetAttackType(UAttackTypes::HEAVY);
			}
		}
	}
}

void UCharacterWolfAnimInstance::AnimNotify_MeleeAtkEnd()
{
	if (GetWorld()->HasBegunPlay())
	{
		bCanAttack = false;
		if (AWeapon_Melee* RecastWeapon = Cast<AWeapon_Melee>(CharacterController->CurrentlyEquippedWeapon))
		{
			RecastWeapon->ToggleCollider();
			RecastWeapon->bHasHit = false;
			RecastWeapon->SetAttackType(UAttackTypes::NONE);
			CharacterController->CurrentMeleeAttackType = UAttackTypes::NONE;
			CharacterController->bIsMeleeAttacking = false;
		}
	}
}

void UCharacterWolfAnimInstance::AnimNotify_ToggleRollState()
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

void UCharacterWolfAnimInstance::AnimNotify_DisableInputAndMakeInvulnerable()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (CharacterController != NULL)
		{
			CharacterController->RevokeControlAndBecomeInvulnerable();
		}
	}
}

void UCharacterWolfAnimInstance::AnimNotify_EnableInputAndRevokeInvulnerable()
{
	if (GetWorld()->HasBegunPlay())
	{
		if (CharacterController != NULL)
		{
			CharacterController->RestoreControlAndRevokeInvulnerable();
		}
	}
}

void UCharacterWolfAnimInstance::AnimNotify_ReplaceMesh()
{

}

