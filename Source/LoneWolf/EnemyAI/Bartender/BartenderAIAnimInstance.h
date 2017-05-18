// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "BartenderAIAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LONEWOLF_API UBartenderAIAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UFUNCTION()
	virtual void AnimNotify_SpawnMolotov();
	UFUNCTION()
	virtual void AnimNotify_EndAttack();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bartender")
	bool bIsAttacking;

	
	class ABartenderAI* Bartender;

	friend class ABartenderAI;

};
