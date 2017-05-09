// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/StatusEffects/StatusEffectBase.h"
#include "StatusEffect_SoftCrowdControl.generated.h"

/**
 * 
 */
UCLASS()
class LONEWOLF_API UStatusEffect_SoftCrowdControl : public UStatusEffectBase
{
	GENERATED_BODY()
	
public:
	UStatusEffect_SoftCrowdControl();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetUpStatusEffect(float DamageToDeal, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterToAfflict, ALoneWolfCharacter* CharacterThatInflictedStatusEffect) override;
	virtual void SetUpStatusEffect(bool bDealDamage, bool bPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterToAfflict, ALoneWolfCharacter* CharacterThatInflictedStatusEffect) override;
	virtual void SetUpStatusEffect(bool bDealDamage, bool bPerformTickAction, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterToAfflict, ALoneWolfCharacter* CharacterThatInflictedStatusEffect) override;
	virtual void ActionToPerformOnStatusTick() override;
	virtual void DestroyComponent(bool bReparentChildren) override;
	
	
};
