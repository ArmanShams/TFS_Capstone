// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "EnemyAI/Sheriff/SheriffAI.h"
#include "SheriffAnimInstance.generated.h"

UCLASS()
class LONEWOLF_API USheriffAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
		//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		//float speed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsDead;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsHardCC;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "enum")
	SheriffState CurrentSheriffSate;

protected:
	UFUNCTION()
	void AnimNotify_Lasso();

	UFUNCTION()
	void AnimNotify_EndPull();

	UFUNCTION()
	void AnimNotify_FirstShot();

	UFUNCTION()
	void AnimNotify_SecondShot();

	UFUNCTION()
	void AnimNotify_EndReload();

	class ASheriffAI* Sheriff;

	friend class ASheriffAI;
};
