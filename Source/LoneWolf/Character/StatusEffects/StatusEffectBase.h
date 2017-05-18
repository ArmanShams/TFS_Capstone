// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "StatusEffectBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LONEWOLF_API UStatusEffectBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatusEffectBase();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetUpStatusEffect(float DamageToDeal, float LifeTime, float TickRate, class ALoneWolfCharacter* CharacterToAfflict, class ALoneWolfCharacter* CharacterThatInflictedStatusEffect);
	virtual void SetUpStatusEffect(bool bDealDamage, bool bPerformTickAction, float LifeTime, float TickRate, class ALoneWolfCharacter* CharacterToAfflict, class ALoneWolfCharacter* CharacterThatInflictedStatusEffect);
	virtual void SetUpStatusEffect(bool bDealDamage, bool bPerformTickAction,  float LifeTime, float DamageToDeal, float TickRate, class ALoneWolfCharacter* CharacterToAfflict, class ALoneWolfCharacter* CharacterThatInflictedStatusEffect);
	virtual void ActionToPerformOnStatusTick();
	virtual void DestroyComponent(bool bReparentChildren) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	float LifeTimeInSeconds;

	UPROPERTY(EditDefaultsOnly)
	float TicksPerSecond;

	UPROPERTY(EditDefaultsOnly)
	float DamagePerTick;


	bool bShouldDealDamage;
	bool bShouldPerformTickAction;
	class ALoneWolfCharacter* AfflictedCharacter;
	class ALoneWolfCharacter* Inflictor;

	float TimeSinceLastTick;
	float TimeAlive;
};
