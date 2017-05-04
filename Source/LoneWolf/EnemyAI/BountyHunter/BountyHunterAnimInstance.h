// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "BountyHunterAnimInstance.generated.h"

UCLASS()
class LONEWOLF_API UBountyHunterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	// Speed of the Bounty Hunter.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float speed;
	// If true, Bounty Hunter is dead. If false, is alive.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsDead;
	// If true, Bounty Hunter is aiming.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsAiming;
	// If true, player is in basic attack range for the Bounty Hunter to shoot.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bCanBasicAttack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsBasicAttack;
	// If true, Bounty Hunter can set a trap at it's location.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bCanSetTrap;
	// Rotator for the mesh.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FRotator LookAtRotation;
	// If true, Bounty Hunter is in hard crowd control.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsHardCC;

protected:
	UFUNCTION()
	void AnimNotify_Shoot();

	UFUNCTION()
	void AnimNotify_PlaceTrap();

	class ABountyHunter* BountyHunter;

	friend class ABountyHunter;
};
