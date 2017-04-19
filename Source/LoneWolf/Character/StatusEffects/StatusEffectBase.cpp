// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "StatusEffectBase.h"
#include "Character/LoneWolfCharacter.h"

// Sets default values for this component's properties
UStatusEffectBase::UStatusEffectBase()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UStatusEffectBase::BeginPlay()
{
	Super::BeginPlay();
}

void UStatusEffectBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (AfflictedCharacter != NULL && Inflictor != NULL)
	{
		if (bShouldPerformTickAction)
		{
			TimeSinceLastTick += DeltaTime;
			if (TimeSinceLastTick >= 1 / TicksPerSecond)
			{
				ActionToPerformOnStatusTick();
				TimeSinceLastTick = 0.f;
			}
		}
		
		TimeAlive += DeltaTime;
		if (TimeAlive >= LifeTimeInSeconds)
		{
			DestroyComponent(true);
		}
	}
}

void UStatusEffectBase::SetUpStatusEffect(float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterToAfflict, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	SetUpStatusEffect(true, true, LifeTime, DamageToDeal, TickRate, CharacterToAfflict, CharacterThatInflictedStatusEffect);
}

void UStatusEffectBase::SetUpStatusEffect(bool bDealDamage, bool bPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterToAfflict, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	SetUpStatusEffect(bDealDamage, bPerformTickAction, LifeTime, 0.f, TickRate, CharacterToAfflict, CharacterThatInflictedStatusEffect);
}

void UStatusEffectBase::SetUpStatusEffect(bool bDealDamage, bool bPerformTickAction, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterToAfflict, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	bShouldDealDamage = bDealDamage;
	bShouldPerformTickAction = bPerformTickAction;
	DamagePerTick = DamageToDeal;
	LifeTimeInSeconds = LifeTime;
	TicksPerSecond = TickRate;
	AfflictedCharacter = CharacterToAfflict;
	Inflictor = CharacterThatInflictedStatusEffect;
}

void UStatusEffectBase::ActionToPerformOnStatusTick()
{
	//DEFINE THE EFFECTS OF THIS EFFECT HERE.
	if (bShouldDealDamage)
	{
		// ONLY DEALS DAMAGE IF bShouldDealDamage is true.
		UGameplayStatics::ApplyDamage(AfflictedCharacter, DamagePerTick, Inflictor->GetController(), Inflictor, TSubclassOf<UDamageType>());
	}
	UE_LOG(LogTemp, Display, TEXT("A status effect performed the action it should perform on a tick!"));
}

void UStatusEffectBase::DestroyComponent(bool bReparentChildren)
{
	Super::UnregisterComponent();
	Super::DestroyComponent(bReparentChildren);
}
