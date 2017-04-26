// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "CharacterHumanAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LONEWOLF_API UCharacterHumanAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;



protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bPrimaryFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bSecondaryFiring;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bRolling;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsDead;

	UFUNCTION()
	void AnimNotify_Reload();

	UFUNCTION()
	void AnimNotify_ToggleRollState();

	class ACharacterController* CharacterController;

	friend class ACharacterController;
};
