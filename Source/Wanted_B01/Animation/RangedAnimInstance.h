// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "RangedAnimInstance.generated.h"

UCLASS()
class WANTED_B01_API URangedAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MovementSpeed;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsShooting;

	UFUNCTION()
	void AnimNotify_StartShooting();

	UFUNCTION()
	void AnimNotify_StopShooting();

	friend class URangedAI;

};
