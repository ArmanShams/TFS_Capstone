// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "CharacterController.h"
#include "PlayerAnimationInstance.h"

void UPlayerAnimationInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (ACharacterController* Character = Cast<ACharacterController>(TryGetPawnOwner()))
	{
		Speed = Character->GetVelocity().Size();
	}
}


