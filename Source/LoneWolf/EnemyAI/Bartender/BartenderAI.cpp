// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BartenderAI.h"




ABartenderAI::ABartenderAI()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Health = MAXHEALTH;

	MoveSpeed = .04f;

	TurnRate = 0.25f;

	MaxRange = 100.0f;

	AttackFrequency = 5.f;

	AttackRange = 250.0f;
	
}

void ABartenderAI::BeginPlay()
{
	Super::BeginPlay();
}

void ABartenderAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABartenderAI::SetupPlayerInputComponent(class UInputComponent* InInputComponent)
{
	Super::SetupPlayerInputComponent(InInputComponent);
}

void ABartenderAI::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::AddStatusEffect(ClassToCreateFrom, bShouldPerformTickAction, LifeTime, TickRate, CharacterThatInflictedStatusEffect);
}

void ABartenderAI::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, bool bShouldDealDamage, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::AddStatusEffect(ClassToCreateFrom, bShouldPerformTickAction, bShouldDealDamage, LifeTime, DamageToDeal, TickRate, CharacterThatInflictedStatusEffect);
}

float ABartenderAI::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

bool ABartenderAI::bIsInRange()
{
	return Super::bIsInRange(AttackRange);
}

bool ABartenderAI::bIsInRange(float OveriddenDesiredRange)
{
	return Super::bIsInRange(OveriddenDesiredRange);
}

AWeapon* ABartenderAI::GetEquippedWeapon()
{
	return Super::GetEquippedWeapon();
}

bool ABartenderAI::bIsSoftCC()
{
	return Super::bIsSoftCC();
}

bool ABartenderAI::bIsHardCC()
{
	return Super::bIsHardCC();
}

CharacterState::StatusEffect ABartenderAI::GetStatusEffect()
{
	return Super::GetStatusEffect();
}

void ABartenderAI::Destroyed()
{
	Super::Destroyed();
}

//void ABartenderAI::EquipWeapon(TSubclassOf<AWeapon> WeaponToEquip)
//{
//	Super::EquipWeapon(WeaponToEquip);
//}
