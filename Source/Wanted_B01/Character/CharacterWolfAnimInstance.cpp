// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "CharacterWolfAnimInstance.h"
#include "Character/CharacterController.h"
#include "Weapons/Weapon.h"
#include "Weapons/Weapon_Melee.h"
#include "Weapons/Weapon_Ranged.h"



void UCharacterWolfAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	CharacterController = Cast<ACharacterController>(TryGetPawnOwner());

	if (CharacterController)
	{
		//UE_LOG(LogTemp, Warning, TEXT("I can attack now"));
		bCanAttack = CharacterController->bIsMeleeAttacking;
		CurrentMeleeAttackType = CharacterController->CurrentMeleeAttackType;
	}
}

void UCharacterWolfAnimInstance::AnimNotify_MeleeAtkStart()
{
	if (bCanAttack)
	{
		UE_LOG(LogTemp, Display, TEXT("We are in the beam"));
		//call a function on our characters to enable colliders on melee weapons
		if (Cast<AWeapon_Melee>(CharacterController->CurrentlyEquippedWeapon))
		{
			Cast<AWeapon_Melee>(CharacterController->CurrentlyEquippedWeapon)->ToggleCollider();
			Cast<AWeapon_Melee>(CharacterController->CurrentlyEquippedWeapon)->SetAttackType(CurrentMeleeAttackType);
		}
	}
}

void UCharacterWolfAnimInstance::AnimNotify_MeleeAtkEnd()
{
	bCanAttack = false;

	if (Cast<AWeapon_Melee>(CharacterController->CurrentlyEquippedWeapon))
	{
		Cast<AWeapon_Melee>(CharacterController->CurrentlyEquippedWeapon)->ToggleCollider();
		Cast<AWeapon_Melee>(CharacterController->CurrentlyEquippedWeapon)->bHasHit = false;
		Cast<AWeapon_Melee>(CharacterController->CurrentlyEquippedWeapon)->SetAttackType(AttackTypes::NONE);
		CharacterController->CurrentMeleeAttackType = AttackTypes::NONE;
		CharacterController->bIsMeleeAttacking = false;
	}
	//call a function on our character to disable colliders on melee weapons
}

