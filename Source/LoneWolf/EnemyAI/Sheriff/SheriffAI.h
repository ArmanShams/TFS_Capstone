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
};

UCLASS()
class LONEWOLF_API ASheriffAI : public AEnemy
{
	GENERATED_BODY()

public:
	ASheriffAI();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect) override;
	virtual void AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, bool bShouldDealDamage, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect) override;

	virtual class AWeapon* EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip) override;
	virtual AWeapon* GetEquippedWeapon();

	virtual bool bIsInRange();
	virtual bool bIsInRange(float OveriddenDesiredRange);
	virtual bool bIsSoftCC() override;
	virtual bool bIsHardCC() override;
	virtual void Destroyed() override;

	SheriffState CurrentState;
	virtual SheriffState GetSheriffState();
	virtual void SetSheriffState(SheriffState NewStateToEnter);

	// Sphere Collider to apply the soft CC
	USphereComponent* LassoSphereCollider;

	// Space to be kept from the Player when Lassoing
	UPROPERTY(EditDefaultsOnly)
		float CushionSpace;
	// Force of lasso
	UPROPERTY(EditDefaultsOnly)
		float PullingForce;
	// Vector of the velocity the player is pulled
	UPROPERTY(EditDefaultsOnly)
		FVector PullingVelocity;
	// Location of the actor
	UPROPERTY(EditDefaultsOnly)
		FVector CurrentLocation;
	// Location of the lasso target
	UPROPERTY(EditDefaultsOnly)
		FVector PlayerLocation;
	// The altered location of the lasso target
	UPROPERTY(EditDefaultsOnly)
		FVector NewLocation;
	// Distance from the lasso target and the Sheriff
	UPROPERTY(EditDefaultsOnly)
		float DistanceToPlayer;
	// How long the lasso is
	UPROPERTY(EditDefaultsOnly)
		float LassoLength;
	// Max attack range for swinging knife
	UPROPERTY(EditDefaultsOnly)
		float KnifeAttackRange;
	// Max attack range for shooting revolver
	UPROPERTY(EditDefaultsOnly)
		float RevolverAttackRange;
	// Max casting range to use lasso
	UPROPERTY(EditDefaultsOnly)
		float LassoAttackRange;

	void SwingKnife();
	void ShootRevolver();
	void Lasso();

	TSubclassOf<AWeapon> KnifeWeapon;
	TSubclassOf<AWeapon> RevolverWeapon;
	TSubclassOf<AWeapon> LassoWeapon;

	FComponentReference CastedPlayerReference;

	UPROPERTY(EditAnywhere)
		class UCableComponent* LassoCableComponent;

	AActor* LassoActor;
	TSubclassOf<AActor> LassoActorClass;

protected:
	friend class USheriffAnimInstance;
	friend class UBTTask_SheriffIdle;
	friend class UBTTask_SheriffLasso;
	friend class UBTTask_SheriffCasting;
	friend class UBTTask_SheriffKnifeAttack;
	friend class UBTTask_SheriffRevolverAttack;
};