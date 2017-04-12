// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "CharacterWolfAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LONEWOLF_API UCharacterWolfAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bCanAttack;

	AttackTypes::MeleeAttackType CurrentMeleeAttackType;

protected:
	UFUNCTION()
	void AnimNotify_MeleeAtkStart();

	UFUNCTION()
	void AnimNotify_MeleeAtkEnd();



	class ACharacterController* CharacterController;

	friend class ACharacterController;

};
