// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyAI/Enemy.h"
#include "SheriffAI.generated.h"

/**
 * 
 */
UCLASS()
class LONEWOLF_API ASheriffAI : public AEnemy
{
	GENERATED_BODY()

public:
	ASheriffAI();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect) override;
	virtual void AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, bool bShouldDealDamage, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect) override;
	virtual AWeapon* GetEquippedWeapon();
	virtual bool bIsInRange();
	virtual bool bIsInRange(float OveriddenDesiredRange);
	virtual bool bIsSoftCC() override;
	virtual bool bIsHardCC() override;
	virtual void Destroyed() override;

	AActor* LassoDecalActor;
	TSubclassOf<AActor> LassoDecalClass;

	void UpdateLassoTelegraph();

	void DisplayLassoTelegraph();


protected:
	virtual void EquipWeapon(TSubclassOf<AWeapon> WeaponToEquip) override;

	friend class USheriffAnimInstance;
};
