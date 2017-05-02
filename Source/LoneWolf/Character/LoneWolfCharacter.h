// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "LoneWolfCharacter.generated.h"

UCLASS()
class LONEWOLF_API ALoneWolfCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALoneWolfCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	/*
		Params
		ClassToCreateFrom					-The static class of an object that derives from UStatusEffectBase to create
		bShouldPerformTickAction			-Whether or not the status effect will perform an action every TickRate seconds
		LifeTime							-How long the status effect will last in seconds
		TickRate							-Every TickRate seconds, if bShouldPerformTickAction is true, the object will call it's ActionToPerformOnTick (For damage over times, how many times per second the damage is applied.
		CharacterThatInflictedStatusEffect	-The character that inflicted the status effect.
	*/
	virtual void AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect);
	/*
		Params
		ClassToCreateFrom					-The static class of an object that derives from UStatusEffectBase to create
		bShouldPerformTickAction			-Whether or not the status effect will perform an action every TickRate seconds
		bShouldDealDamage					-Whether or not this status effect will deal damage when it's tick action is performed.
		LifeTime							-How long the status effect will last in seconds
		DamageToDeal						-Amount of damage dealt to the actor inflicted by the status effect.
		TickRate							-Every TickRate seconds, if bShouldPerformTickAction is true, the object will call it's ActionToPerformOnTick (For damage over times, how many times per second the damage is applied.
		CharacterThatInflictedStatusEffect	-The character that inflicted the status effect.
	*/
	virtual void AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, bool bShouldDealDamage, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect);
	virtual bool GetbIsInHardCC();
	virtual bool GetbIsInSoftCC();
	virtual class AWeapon* EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip);
	virtual class AWeapon* GetEquippedWeapon();
	virtual void Destroyed() override;


protected:
	virtual bool bIsHardCC();
	virtual bool bIsSoftCC();
	virtual void Die();

	bool bIsInHardCC;
	bool bIsInSoftCC;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	float MoveSpeedBase;

	float MoveSpeedActual;

	class AWeapon* CurrentlyEquippedWeapon;

};
