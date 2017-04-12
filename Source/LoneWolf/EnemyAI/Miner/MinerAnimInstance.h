// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "MinerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LONEWOLF_API UMinerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UFUNCTION()
	virtual void AnimNotify_MeleeAtkStart();

	UFUNCTION()
	virtual void AnimNotify_MeleeAtkEnd();

	UFUNCTION()
	virtual void AnimNotify_ChargeEnd();

	UFUNCTION()
	virtual void AnimNotify_ReturnToIdle();


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bCanAttack;

	UPROPERTY(BlueprintReadOnly)
	MinerState CurrentMinerState;

	CharacterState::StatusEffect Effects;
	
	class AEnemy* EnemyCharacter;

	friend class AEnemy;
	friend class AMinerAI;
	friend class AMinerAIController;
	
	
};
