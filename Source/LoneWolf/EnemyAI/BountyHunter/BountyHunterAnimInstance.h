// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "BountyHunterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LONEWOLF_API UBountyHunterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	


public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float speed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		bool isDead;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		bool bCanBasicAttack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		bool bCanSetTrap;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FRotator LookAtRotation;

protected:
	UFUNCTION()
		void AnimNotify_BasicAttackShot();

	UFUNCTION()
		void AnimNotify_PlaceTrap();



	class ABountyHunter* BountyHunter;

	friend class ABountyHunter;
	
	
};
