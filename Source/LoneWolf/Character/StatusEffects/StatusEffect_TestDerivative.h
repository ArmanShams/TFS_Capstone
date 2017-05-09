// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/StatusEffects/StatusEffect_HardCrowdControl.h"
#include "StatusEffect_TestDerivative.generated.h"

/**
 * 
 */
UCLASS()
class LONEWOLF_API UStatusEffect_TestDerivative : public UStatusEffect_HardCrowdControl
{
	GENERATED_BODY()
	
public:
	UStatusEffect_TestDerivative();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetUpStatusEffect(float DamageToDeal, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterToAfflict, ALoneWolfCharacter* CharacterThatInflictedStatusEffect) override;
	virtual void SetUpStatusEffect(bool bDealDamage, bool bPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterToAfflict, ALoneWolfCharacter* CharacterThatInflictedStatusEffect) override;
	virtual void SetUpStatusEffect(bool bDealDamage, bool bPerformTickAction, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterToAfflict, ALoneWolfCharacter* CharacterThatInflictedStatusEffect) override;
	virtual void ActionToPerformOnStatusTick() override;
	virtual void DestroyComponent(bool bReparentChildren) override;

};
