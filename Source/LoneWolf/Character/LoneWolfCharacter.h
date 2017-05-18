// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Weapons/WeaponTypes.h"
#include "Character/StatusEffects/StatusEffects.h"
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

		Instantiates a new UStateEffectBase and attaches it to this actor, adding it to the actor's ActorComponents array.
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

		Instantiates a new UStateEffectBase and attaches it to this actor, adding it to the actor's ActorComponents array.
	*/
	virtual void AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, bool bShouldDealDamage, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect);
	/*
		Returns true if the character has at least one hard status effect actor component
	*/
	virtual bool GetbIsInHardCC();
	/*
		Returns true if the character has at least one soft status effect actor component
	*/
	virtual bool GetbIsInSoftCC();
	/*
		Params
		TSubclassOf<AWeapon> WeaponToEquip		-The class of weapon to instantiate

		Instantiates an actor of type AWeapon and attaches it to bone "Hand_r" of this actor's skeletal mesh
		If the actor's skeleton does not have bone "Hand_r" it will assign to a bone arbitrarily
	*/
	virtual class AWeapon* EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip);
	/*
		Returns a pointer to currently member EquippedWeapon if it isn't null
	*/
	virtual class AWeapon* GetEquippedWeapon();
	virtual void Destroyed() override;

protected:
	/*
		Returns true if the character has at least one hard status effect actor component
	*/
	virtual bool bIsHardCC();
	/*
		Returns true if the character has at least one soft status effect actor component
	*/
	virtual bool bIsSoftCC();
	/*
		Override this to destroy any spawned decals or objects that need their removal handled before the actor is destroyed by the garbage collector.
	*/
	virtual void Die();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	// Assigned by member function bIsHardCC()
	bool bIsInHardCC;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	// Assigned by member function bIsSoftCC()
	bool bIsInSoftCC;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	float MoveSpeedBase;

	float MoveSpeedActual;

	class AWeapon* CurrentlyEquippedWeapon;

};
