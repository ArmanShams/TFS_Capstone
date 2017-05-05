// Fill out your copyright notice in the Description page of Project Settings.
// this is the enemy base class which will derive the enemys health, attacks, and status effects.

#pragma once

#include "GameFramework/Character.h"
#include "Character/LoneWolfCharacter.h"
#include "Weapons/Weapon.h"
#include "Weapons/Weapon_Melee.h"
#include "Weapons/Weapon_Ranged.h"
#include "Enemy.generated.h"


UENUM(BlueprintType)
enum class EState : uint8
{
	Idle			UMETA(DisplayName = "Idle"),
	Search			UMETA(DisplayName = "Search"),
	Attack			UMETA(DisplayName = "Attack"),
	Flee			UMETA(DisplayName = "Flee")
};

UCLASS(Blueprintable)
class LONEWOLF_API AEnemy : public ALoneWolfCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect) override;
	virtual void AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, bool bShouldDealDamage, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect) override;
	virtual bool GetbIsInHardCC() override;
	virtual bool GetbIsInSoftCC() override;
	virtual AWeapon* GetEquippedWeapon() override;
	virtual bool bIsInRange();
	virtual bool bIsInRange(float OveriddenDesiredRange);
	
	virtual void Destroyed() override;


	virtual CharacterState::StatusEffect GetStatusEffect();

	UPROPERTY(EditInstanceOnly)
	TArray<class ATargetPoint*> PatrolPoints;

protected:
	// Returns true if the actor's Status Effects is a 'softCC'. Defined in Design Document
	virtual bool bIsSoftCC() override;
	// Returns true if the actor's Status Effects is a 'hardCC'. Defined in Design Document
	virtual bool bIsHardCC() override;

	virtual void Die() override;

	virtual AWeapon* EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip) override;
	//virtual void EquipWeapon(TSubclassOf<AWeapon> WeaponToEquip);
	virtual void SetStatusEffect(CharacterState::StatusEffect NewStatusEffect);



	UPROPERTY(EditDefaultsOnly)
	float Health;

	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed;

	UPROPERTY(EditDefaultsOnly)
	float TurnRate;

	UPROPERTY(EditDefaultsOnly)
	float MaxRange;

	float TimeSinceLastAttack;

	UPROPERTY(EditDefaultsOnly)
	float AttackFrequency;

	UPROPERTY(EditDefaultsOnly)
	float AttackRange;

	UPROPERTY(EditDefaultsOnly)
	float DespawnTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	EState EnemyState;

	CharacterState::StatusEffect Effects;
	TSubclassOf<AWeapon> DefaultWeapon;
	class AWeapon* CurrentlyEquippedWeapon;

	friend class UEnemyAnimInstance;
	friend class UMinerAnimInstance;

	const float MAXHEALTH = 100.f;
};
