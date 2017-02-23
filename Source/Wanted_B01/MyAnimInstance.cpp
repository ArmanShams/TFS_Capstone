// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "CharacterController.h"
#include "MyAnimInstance.h"


void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (ACharacterController* Character = Cast<ACharacterController>(TryGetPawnOwner()))
	{
		Speed = Character->GetVelocity().Size();
	}
}

void UMyAnimInstance::AnimNotify_AttackStart()
{
	//call a function on our characters to enable colliders on melee weapons
}

void UMyAnimInstance::AnimNotify_AttackEnd()
{
	bIsAttacking = false;

	//call a function on our character to disable colliders on melee weapons
}
