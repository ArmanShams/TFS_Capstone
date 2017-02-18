// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "PlayerAnimationInstance.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_B01_API UPlayerAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds);

protected:
	UPROPERTY(EditDefaultsOnly)
	float Speed;
	
	UPROPERTY(EditDefaultsOnly)
	bool bIsAttacking;
	
};
