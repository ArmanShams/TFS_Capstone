// Fill out your copyright notice in the Description page of Project Settings

#pragma once

#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"


UCLASS()
class WANTED_B01_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bCanAttack;

protected:
	UFUNCTION()
		void AnimNotify_MeleeAtkStart();

	UFUNCTION()
		void AnimNotify_MeleeAtkEnd();

	class AEnemy* EnemyCharacter;

	friend class AEnemy;
};
