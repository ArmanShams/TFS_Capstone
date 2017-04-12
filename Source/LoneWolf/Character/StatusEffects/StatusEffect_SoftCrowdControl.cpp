// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "StatusEffect_SoftCrowdControl.h"




UStatusEffect_SoftCrowdControl::UStatusEffect_SoftCrowdControl()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UStatusEffect_SoftCrowdControl::BeginPlay()
{
	Super::BeginPlay();
}

void UStatusEffect_SoftCrowdControl::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UStatusEffect_SoftCrowdControl::SetUpStatusEffect(float DamageToDeal, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterToAfflict, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::SetUpStatusEffect(DamageToDeal, LifeTime, TickRate, CharacterToAfflict, CharacterThatInflictedStatusEffect);
}

void UStatusEffect_SoftCrowdControl::SetUpStatusEffect(bool bDealDamage, bool bPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterToAfflict, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::SetUpStatusEffect(bDealDamage, bPerformTickAction, LifeTime, TickRate, CharacterToAfflict, CharacterThatInflictedStatusEffect);
}

void UStatusEffect_SoftCrowdControl::SetUpStatusEffect(bool bDealDamage, bool bPerformTickAction, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterToAfflict, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::SetUpStatusEffect(bDealDamage, bPerformTickAction, LifeTime, DamageToDeal, TickRate, CharacterToAfflict, CharacterThatInflictedStatusEffect);
}

void UStatusEffect_SoftCrowdControl::ActionToPerformOnStatusTick()
{
	Super::ActionToPerformOnStatusTick();
}

void UStatusEffect_SoftCrowdControl::DestroyComponent(bool bReparentChildren)
{
	Super::DestroyComponent(bReparentChildren);
}
