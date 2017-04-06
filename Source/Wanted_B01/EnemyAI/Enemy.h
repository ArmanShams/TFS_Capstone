// Fill out your copyright notice in the Description page of Project Settings.
// this is the enemy base class which will derive the enemys health, attacks, and status effects.

#pragma once

#include "GameFramework/Character.h"
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
class WANTED_B01_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual AWeapon* GetEquippedWeapon();
	virtual bool bIsInRange();
	virtual bool bIsInRange(float OveriddenDesiredRange);
	// Returns true if the actor's Status Effects is a 'softCC'. Defined in Design Document
	virtual bool bIsSoftCC();
	// Returns true if the actor's Status Effects is a 'hardCC'. Defined in Design Document
	virtual bool bIsHardCC();
	


	virtual CharacterState::StatusEffect GetStatusEffect();

	UPROPERTY(EditInstanceOnly)
	TArray<class ATargetPoint*> PatrolPoints;

protected:
	virtual void EquipWeapon(TSubclassOf<AWeapon> WeaponToEquip);
	virtual void SetStatusEffect(CharacterState::StatusEffect NewStatusEffect);

	UPROPERTY(EditDefaultsOnly)
	float Health;

	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed;

	UPROPERTY(EditDefaultsOnly)
	float TurnRate;

	UPROPERTY(EditDefaultsOnly)
	float MaxRange;

	UPROPERTY(EditDefaultsOnly)
	float TimeSinceLastAttack;

	UPROPERTY(EditDefaultsOnly)
	float AttackFrequency;

	UPROPERTY(EditDefaultsOnly)
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	EState EnemyState;

	CharacterState::StatusEffect Effects;
	TSubclassOf<AWeapon> DefaultWeapon;
	class AWeapon* CurrentlyEquippedWeapon;

	friend class UEnemyAnimInstance;
	friend class UMinerAnimInstance;

	const float MAXHEALTH = 100.f;

	//Unused variables
	/*
	// cooldown for how frequently the skills can be used
	UPROPERTY(EditAnywhere)
	float Skill1Cooldown;

	// cooldown for how frequently the skills can be used
	UPROPERTY(EditAnywhere)
	float Skill2Cooldown;

	UPROPERTY(EditAnywhere)
	float isInRange;
	*/

	// Unused functionality
	/*
	int32 AttackType;

	void Attack(int32 AttackType);

	//enemy's basic attack which will be most frequently used can include input for status effect application
	void BasicAttack(Effects effect, float Range);

	void AttackEnd();

	//enemy's 1st skill, will include an input for status effect application
	void Skill1(Effects effect, float Range);

	//enemy's 1st skill, will include an input for status effect application
	void Skill2(Effects effect, float Range);
	*/

	

};
