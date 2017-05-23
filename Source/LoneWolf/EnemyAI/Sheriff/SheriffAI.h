// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyAI/Enemy.h"
#include "Character/PlayerCharacter/CharacterController.h"
#include "SheriffAI.generated.h"

UENUM(BlueprintType)
enum class SheriffState : uint8
{
	IDLE			UMETA(DisplayName = "Idle"),
	MELEE			UMETA(DisplayName = "Melee"),
	RANGED			UMETA(DisplayName = "Ranged"),
	CASTING			UMETA(DisplayName = "Casting"),
	LASSO			UMETA(DisplayName = "Lasso"),
	HARDCC			UMETA(DisplayName = "HardCC")
};

UCLASS()
class LONEWOLF_API ASheriffAI : public AEnemy
{
	GENERATED_BODY()

public:
	ASheriffAI();
	//Inherited public functions from AEnemy
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InInputComponent) override;
	virtual void AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect) override;
	virtual void AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, bool bShouldDealDamage, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect) override;
	virtual AWeapon* GetEquippedWeapon() override;
	virtual bool bIsInRange() override;
	virtual bool bIsInRange(float OveriddenDesiredRange) override;
	virtual CharacterState::StatusEffect GetStatusEffect() override;
	virtual bool GetbIsInHardCC() override;
	virtual bool GetbIsInSoftCC() override;
	virtual void Destroyed() override;
	virtual bool bIsSoftCC() override;
	virtual bool bIsHardCC() override;
	virtual void Die() override;

	// Implemented public functions
	virtual SheriffState GetSheriffState();

protected: //Inherited protected functions from AEnemy
	virtual AWeapon* EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip) override;

protected: //Implemented Functions
	void Lasso();
	void Shoot();
	void Casting();
	void SwingKnife();

	SheriffState CurrentState;
	virtual void SetSheriffState(SheriffState NewStateToEnter);

	// Sphere Collider to apply the soft CC
	USphereComponent* LassoSphereCollider;

protected: // Variables to keep track
		   //Space to be kept from the Player when Lassoing
	UPROPERTY(EditDefaultsOnly)
		float CushionSpace;
	//Force of lasso
	UPROPERTY(EditDefaultsOnly)
		float PullingForce;
	//Vector of the velocity the player is pulled
	UPROPERTY(EditDefaultsOnly)
		FVector PullingVelocity;
	//Location of the actor
	UPROPERTY(EditDefaultsOnly)
		FVector CurrentLocation;
	//Location of the lasso target
	UPROPERTY(EditDefaultsOnly)
		FVector PlayerLocation;
	//The altered location of the lasso target
	UPROPERTY(EditDefaultsOnly)
		FVector NewLocation;
	//Distance from the lasso target and the Sheriff
	UPROPERTY(EditDefaultsOnly)
		float DistanceToPlayer;
	//How long the lasso is
	UPROPERTY(EditDefaultsOnly)
		float LassoLength;
	//Max attack range for swinging knife
	UPROPERTY(EditDefaultsOnly)
		float KnifeAttackRange;
	//Max attack range for shooting revolver
	UPROPERTY(EditDefaultsOnly)
		float RevolverAttackRange;
	//Max casting range to use lasso
	UPROPERTY(EditDefaultsOnly)
		float LassoAttackRange;

protected: //Decal Actors
	AActor* LassoLineDecalActor;
	TSubclassOf<AActor> LassoLineDecalClass;

protected: //Weapons
	AActor* LassoActor;
	TSubclassOf<AActor> LassoActorClass;
	TSubclassOf<AWeapon> KnifeWeapon;
	TSubclassOf<AWeapon> ShotgunWeapon;
	TSubclassOf<AWeapon> LassoWeapon;

	FComponentReference CastedPlayerReference;

	UPROPERTY(EditAnywhere)
		class UCableComponent* LassoCableComponent;

protected: //Blackboard Key Booleans
	bool bSafeAttackingDistance();
	bool bIsFlee();
	bool bIsStunned;
	bool bIsFleeing;

	void Aim(ACharacterController* PlayerToAimAt);

	//Animation Booleans
	bool bCanAttack;
	bool bIsBasicAttack;
	bool bIsAiming;
	bool bIsPlacingTrap;

	//Not Yet Implemented Functions
	bool bIsCasting();


protected: //Friendships
	friend class USheriffAnimInstance;
	friend class UBTTask_SheriffIdle;
	friend class UBTTask_SheriffLasso;
	friend class UBTTask_SheriffCasting;
	friend class UBTTask_SheriffKnifeAttack;
	friend class UBTTask_SheriffShotgunAttack;
};