// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyAI/Enemy.h"
#include "MinerAI.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_B01_API AMinerAI : public AEnemy
{
	GENERATED_BODY()
	
public:
	AMinerAI();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual bool bIsInRange() override;
	virtual bool bIsInRange(float OveriddenDesiredRange) override;

	// How often in seconds the Miner can use his charge.
	UPROPERTY(EditDefaultsOnly)
	float ChargeCooldown;

	// The distance the Miner will be able to use the Charge, not the length of the charge itself.
	UPROPERTY(EditDefaultsOnly)
	float DistanceToUseCharge;
	
protected:
	float TimeSinceLastCharge;
	//virtual void EquipWeapon() override;

};
