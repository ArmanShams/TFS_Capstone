// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "CharacterWolfAnimInstance.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class AttackTypeWrapper : uint8
{
	NONE		UMETA(DisplayName = "None"),
	LIGHT		UMETA(DisplayName = "Light"),
	HEAVY		UMETA(DisplayName = "Heavy")
};

UCLASS()
class LONEWOLF_API UCharacterWolfAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bCanAttack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AnimMovementSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AnimMovementDirection;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AimOffsetYaw;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bRolling;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsDead;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsInHardCC;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsInSoftCC;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ForwardMovementMultiplier;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TransformationState CurrentForm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AttackType")
	AttackTypeWrapper AttackType;

	UAttackTypes::MeleeAttackType CurrentMeleeAttackType;

	UFUNCTION()
	void AnimNotify_MeleeAtkStart();

	UFUNCTION()
	void AnimNotify_MeleeAtkEnd();

	UFUNCTION()
	void AnimNotify_ToggleRollState();

	UFUNCTION()
	void AnimNotify_DisableInputAndMakeInvulnerable();

	UFUNCTION()
	void AnimNotify_EnableInputAndRevokeInvulnerable();

	UFUNCTION()
	void AnimNotify_ReplaceMesh();

	class ACharacterController* CharacterController;

	friend class ACharacterController;

};
