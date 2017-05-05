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
	float AnimMovementSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AnimMovementDirection;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bPrimaryFire;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bSecondaryFiring;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bRolling;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsDead;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bReloading;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsInHardCC;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsInSoftCC;


	UFUNCTION()
	void AnimNotify_Reload();

	UFUNCTION()
	void AnimNotify_ReloadEnd();

	UFUNCTION()
	void AnimNotify_ToggleRollState();

	UFUNCTION()
	void AnimNotify_EndPrimaryFire();




	class ACharacterController* CharacterController;

	friend class ACharacterController;
};
