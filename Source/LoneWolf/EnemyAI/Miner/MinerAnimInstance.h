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
	virtual void AnimNotify_MeleeAttackStart();

	UFUNCTION()
	virtual void AnimNotify_MeleeAttackEnd();

	UFUNCTION()
	virtual void AnimNotify_ChargeEnd();

	UFUNCTION()
	virtual void AnimNotify_Stomp();

	UFUNCTION()
	virtual void AnimNotify_ReturnToIdle();


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bCanAttack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsDead;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsInHardCC;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsInSoftCC;

	UPROPERTY(BlueprintReadOnly)
	MinerState CurrentMinerState;

	CharacterState::StatusEffect Effects;
	
	class AMinerAI* EnemyCharacter;

	friend class AEnemy;
	friend class AMinerAI;
	friend class AMinerAIController;
	
	
};
