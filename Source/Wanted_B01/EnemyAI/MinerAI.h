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
	
protected:
	//virtual void EquipWeapon() override;

};
