// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyAI/Enemy.h"
#include "BartenderAI.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_B01_API ABartenderAI : public AEnemy
{
	GENERATED_BODY()
	
public:
	ABartenderAI();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual bool bIsInRange() override;
	virtual bool bIsInRange(float OveriddenDesiredRange) override;
	virtual float DamageOverTime(float FireDOT);
	
	// How often in seconds the Bartender uses their Fire Breath attack
	UPROPERTY(EditDefaultsOnly)
	float FireBreathCooldown;

	// The distance the Bartender can use the Fire Breath
	UPROPERTY(EditDefaultsOnly)
	float DistanceToUseFB;

	//How often in seconds the Bartender uses their Keg Roll attack
	UPROPERTY(EditDefaultsOnly)
	float KegRollCooldown;
	
	// The distance the bartender can use the Keg Roll
	UPROPERTY(EditDefaultsOnly)
	float DistanceToUseKegRoll;

	//Fire Damage Over Time	
	UPROPERTY(EditDefaultsOnly)
	float FireDOT;

protected:
	float TimeSinceLastFB;

	float TimeSinceLastKR;

	
	
};
