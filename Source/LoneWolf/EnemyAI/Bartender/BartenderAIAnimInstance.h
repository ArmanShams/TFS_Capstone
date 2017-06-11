// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "BartenderAIAnimInstance.generated.h"

UCLASS()
class LONEWOLF_API UBartenderAIAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsDead;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsInHardCC;

	UFUNCTION()
	virtual void AnimNotify_SpawnMolotov();
	UFUNCTION()
	virtual void AnimNotify_EndAttack();
	UFUNCTION(BlueprintImplementableEvent, category = "Enemy")
	void OnDamageTaken();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bartender")
	bool bIsAttacking;

	
	class ABartenderAI* Bartender;

	friend class ABartenderAI;

};
