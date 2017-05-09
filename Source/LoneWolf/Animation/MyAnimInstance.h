// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

UCLASS()
class LONEWOLF_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Speed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsAttacking;

protected:
	UFUNCTION()
	void AnimNotify_AttackStart();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	
};
