// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "EnemyAI/EnemyAnimInstance.h"
#include "EnemyAI/Enemy.h"


void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AEnemy* EnemyCharacter = Cast<AEnemy>(TryGetPawnOwner());

	if (EnemyCharacter)
	{
		//UE_LOG(LogTemp, Warning, TEXT("I can attack now"));
		bCanAttack = EnemyCharacter->bIsAttacking();
	}
}

void UEnemyAnimInstance::AnimNotify_MeleeAtkStart()
{
	if (bCanAttack == true)
	{
		//call a function on our characters to enable colliders on melee weapons
	}
}

void UEnemyAnimInstance::AnimNotify_MeleeAtkEnd()
{
	bCanAttack = false;

	//call a function on our character to disable colliders on melee weapons
}
