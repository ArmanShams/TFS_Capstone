// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "EnemyAI/EnemyAnimInstance.h"
#include "EnemyAI/Enemy.h"


void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (AEnemy* EnemyCharacter = Cast<AEnemy>(TryGetPawnOwner()))
	{
		bCanAttack = EnemyCharacter->bIsAttacking();
	}
}

