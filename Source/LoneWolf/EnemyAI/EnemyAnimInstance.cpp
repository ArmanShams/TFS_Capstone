// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "EnemyAI/EnemyAnimInstance.h"
#include "EnemyAI/Enemy.h"
#include "Weapons/Weapon.h"
#include "Weapons/Weapon_Melee.h"
#include "Weapons/Weapon_Ranged.h"



void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	EnemyCharacter = Cast<AEnemy>(TryGetPawnOwner());

	if (EnemyCharacter)
	{
		//UE_LOG(LogTemp, Warning, TEXT("I can attack now"));
		bCanAttack = EnemyCharacter->bIsInRange();
		/*if (bCanAttack)
		{
			UE_LOG(LogTemp, Warning, TEXT("I can attack now"));
		}*/
	}
}

void UEnemyAnimInstance::AnimNotify_MeleeAtkStart()
{
	if (bCanAttack)
	{
		//UE_LOG(LogTemp, Display, TEXT("We are in the beam"));
		//call a function on our characters to enable colliders on melee weapons
		if (Cast<AWeapon_Melee>(EnemyCharacter->CurrentlyEquippedWeapon))
		{
			Cast<AWeapon_Melee>(EnemyCharacter->CurrentlyEquippedWeapon)->ToggleCollider();
		}
	}
}

void UEnemyAnimInstance::AnimNotify_MeleeAtkEnd()
{
	bCanAttack = false;

	if (Cast<AWeapon_Melee>(EnemyCharacter->CurrentlyEquippedWeapon))
	{
		Cast<AWeapon_Melee>(EnemyCharacter->CurrentlyEquippedWeapon)->ToggleCollider();
		Cast<AWeapon_Melee>(EnemyCharacter->CurrentlyEquippedWeapon)->bHasHit = false;
	}
	//call a function on our character to disable colliders on melee weapons
}
