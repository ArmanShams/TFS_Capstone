// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "SheriffAnimInstance.generated.h"

UCLASS()
class LONEWOLF_API USheriffAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float speed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float KnifeRange;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float RevolverRange;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float LassoRange;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		bool isDead;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		bool bKnifeSwing;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		bool bShootRevolver;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		bool bCanLassoAttack;

protected:
	UFUNCTION()
		void AnimNotify_KnifeSwing();

	UFUNCTION()
		void AnimNotify_ShootRevolver();

	UFUNCTION()
		void AnimNotify_LassoAttack();

	class ASheriffAI* SheriffAI;

	friend class ASheriffAI;
};
