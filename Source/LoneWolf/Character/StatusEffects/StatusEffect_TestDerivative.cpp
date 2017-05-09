// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "StatusEffect_TestDerivative.h"



UStatusEffect_TestDerivative::UStatusEffect_TestDerivative()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UStatusEffect_TestDerivative::BeginPlay()
{
	Super::BeginPlay();
}

void UStatusEffect_TestDerivative::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UStatusEffect_TestDerivative::SetUpStatusEffect(float DamageToDeal, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterToAfflict, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::SetUpStatusEffect(DamageToDeal, LifeTime, TickRate, CharacterToAfflict, CharacterThatInflictedStatusEffect);
}

void UStatusEffect_TestDerivative::SetUpStatusEffect(bool bDealDamage, bool bPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterToAfflict, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::SetUpStatusEffect(bDealDamage, bPerformTickAction, LifeTime, TickRate, CharacterToAfflict, CharacterThatInflictedStatusEffect);
}

void UStatusEffect_TestDerivative::SetUpStatusEffect(bool bDealDamage, bool bPerformTickAction, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterToAfflict, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::SetUpStatusEffect(bDealDamage, bPerformTickAction, LifeTime, DamageToDeal, TickRate, CharacterToAfflict, CharacterThatInflictedStatusEffect);
}

void UStatusEffect_TestDerivative::ActionToPerformOnStatusTick()
{
	Super::ActionToPerformOnStatusTick();
}

void UStatusEffect_TestDerivative::DestroyComponent(bool bReparentChildren)
{
	Super::DestroyComponent(bReparentChildren);
}
