// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "StatusEffect_HardCrowdControl.h"


UStatusEffect_HardCrowdControl::UStatusEffect_HardCrowdControl()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	LifeTimeInSeconds = 5.f;
	TicksPerSecond = 1.0f;
	DamagePerTick = 5.0f;
}

void UStatusEffect_HardCrowdControl::BeginPlay()
{
	Super::BeginPlay();

}

void UStatusEffect_HardCrowdControl::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}



void UStatusEffect_HardCrowdControl::SetUpStatusEffect(float DamageToDeal, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterToAfflict, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::SetUpStatusEffect(DamageToDeal, LifeTime, TickRate, CharacterToAfflict, CharacterThatInflictedStatusEffect);
}

void UStatusEffect_HardCrowdControl::SetUpStatusEffect(bool bDealDamage, bool bPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterToAfflict, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::SetUpStatusEffect(bDealDamage, bPerformTickAction, LifeTime, TickRate, CharacterToAfflict, CharacterThatInflictedStatusEffect);
}

void UStatusEffect_HardCrowdControl::SetUpStatusEffect(bool bDealDamage, bool bPerformTickAction, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterToAfflict, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::SetUpStatusEffect(bDealDamage, bPerformTickAction, LifeTime, DamageToDeal, TickRate, CharacterToAfflict, CharacterThatInflictedStatusEffect);
}

void UStatusEffect_HardCrowdControl::ActionToPerformOnStatusTick()
{
	Super::ActionToPerformOnStatusTick();
}

void UStatusEffect_HardCrowdControl::DestroyComponent(bool bReparentChildren)
{
	Super::DestroyComponent(bReparentChildren);
}
