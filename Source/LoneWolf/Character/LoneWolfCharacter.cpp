// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "LoneWolfCharacter.h"
#include "Character/StatusEffects/StatusEffectBase.h"
#include "Character/StatusEffects/StatusEffect_HardCrowdControl.h"
#include "Character/StatusEffects/StatusEffect_SoftCrowdControl.h"

ALoneWolfCharacter::ALoneWolfCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALoneWolfCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALoneWolfCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALoneWolfCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

float ALoneWolfCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ALoneWolfCharacter::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	UStatusEffectBase* Effect = NewObject<UStatusEffectBase>(this, ClassToCreateFrom);

	this->AddOwnedComponent(Effect);
	Effect->RegisterComponent();
	Effect->SetUpStatusEffect(false, bShouldPerformTickAction, LifeTime, TickRate, this, CharacterThatInflictedStatusEffect);
}

void ALoneWolfCharacter::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, bool bShouldDealDamage, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	UStatusEffectBase* Effect = NewObject<UStatusEffectBase>(this, ClassToCreateFrom);

	this->AddOwnedComponent(Effect);
	Effect->RegisterComponent();
	Effect->SetUpStatusEffect(bShouldDealDamage, bShouldPerformTickAction, LifeTime, DamageToDeal, TickRate, this, CharacterThatInflictedStatusEffect);
}

bool ALoneWolfCharacter::bIsHardCC()
{
	if (GetComponentByClass(UStatusEffect_HardCrowdControl::StaticClass()))
	{
		//UE_LOG(LogTemp, Display, TEXT("WE ARE IN THE CC"));
		return true;
	}
	return false;
}

bool ALoneWolfCharacter::bIsSoftCC()
{
	if (bIsHardCC())
	{
		return true;
	}
	if (GetComponentByClass(UStatusEffect_SoftCrowdControl::StaticClass()))
	{
		//UE_LOG(LogTemp, Display, TEXT("WE ARE IN THE CC"));
		return true;
	}
	return false;
}

