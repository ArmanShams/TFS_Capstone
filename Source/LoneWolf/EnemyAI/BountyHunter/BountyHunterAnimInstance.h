// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "EnemyAI/BountyHunter/BountyHunter.h"
#include "BountyHunterAnimInstance.generated.h"

UCLASS()
class LONEWOLF_API UBountyHunterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	//Current state that the Bounty Hunter is in.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "enum")
	BountyHunterState CurrentBountyHunterState;

	//Speed of the Bounty Hunter.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float speed;

	//If true, Bounty Hunter is dead. If false, is alive.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsDead;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsSettingTrap;
				
	//If true, Bounty Hunter is in hard crowd control.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsHardCC;

	UFUNCTION()
	void AnimNotify_ReturnToIdle();

	UFUNCTION()
	void AnimNotify_Aiming();

	UFUNCTION()
	void AnimNotify_StartShooting();

	UFUNCTION()
	void AnimNotify_EndShooting();

	UFUNCTION()
	void AnimNotify_PlaceTrap();

	UFUNCTION(BlueprintImplementableEvent, category = "Enemy")
	void OnDamageTaken();

	class ABountyHunter* BountyHunter;

	friend class AEnemy;
	friend class ABountyHunter;
	friend class ABountyHunterAIController;
};