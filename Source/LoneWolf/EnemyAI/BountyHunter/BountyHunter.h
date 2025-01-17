// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyAI/Enemy.h"
#include "BountyHunter.generated.h"

UENUM(BlueprintType)
enum class BountyHunterState : uint8
{
	IDLE					UMETA(DisplayName = "Idle"),
	AIMING					UMETA(DisplayName = "Aiming"),
	ATTACKING				UMETA(DisplayName = "Attacking"),
	FLEEING					UMETA(DisplayName = "Fleeing"),
	HARDCC					UMETA(DisplayName = "Stunned"),
	SETTINGTRAP				UMETA(DisplayName = "SettingTrap")
};

UCLASS(Blueprintable)
class LONEWOLF_API ABountyHunter : public AEnemy
{
	GENERATED_BODY()

public:
	ABountyHunter();

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

	// Implemented public functions
	virtual BountyHunterState GetBountyHunterState();

//Inherited protected functions from AEnemy
protected: 
	virtual bool bIsSoftCC() override;
	virtual bool bIsHardCC() override;
	virtual void Die() override;
	virtual AWeapon* EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip) override;

//Implemented Functions
protected: 
	virtual void Attack();
	virtual void FixWeaponRotation();
	virtual void SetBearTrap(class ATrapLocations* NewTrapLocation, const FHitResult & SweepResult);
	virtual void DecrementActiveBearTraps(ABearTrap* TrapToRemove);

	UFUNCTION()
	virtual void OnComponentOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void SetBountyHunterState(BountyHunterState NewState);

	void Aim(class ACharacterController* Player);

protected:
	//The maximum number of traps he is allowed to put in the world, extra traps will delete the obsolete trap.
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
	uint8 MaximumTrapsAllowed;
	//Cushion distance from player, safe distance to attack.
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
	float CushionSpace;
	//Decal Actor to display telegraphs, and an array to store decal class created.
	AActor* AimLineDecalActor;
	TSubclassOf<AActor> AimLineDecalClass;
	//BearTrap Actor to place in the world, and an array to store bear trap class created.
	TSubclassOf<class ABearTrap> BearTrapClass;
	ABearTrap* BearTrapPlaced;
	//Array to keep track of how many traps are in the world, and pop the obsolete trap.
	TArray<AActor*> TrapArray;
	//Bounty Hunter Enumerator current state to control animations and functions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	BountyHunterState CurrentState;
	//Check on BlackBoard Component target, flee from player character when conditions are met.
	class ACharacterController* PlayerRecasted;

protected: //Blackboard Key Booleans
	bool bIsStunned;
	bool bIsFleeing;

	//Booleans to check for range
	bool bAttack;
	bool bFlee;
	bool bPatrol;

	FVector CurrentLocation;
	FVector PlayerLocation;
	FRotator RotationToPlayer;
	FVector DirectionToFace;
	FRotator Rotator;

	float DistanceToPlayer;


	//Booleans for animation
	bool bShouldAdjustGun;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	bool bIsPlacingTrap;

	//Friendships
	friend class ABearTrap;
	friend class UBountyHunterAnimInstance;
	friend class UBTTask_BountyHunterAim;
	friend class UBTTask_BountyHunterFlee;
	friend class UBTTask_BountyHunterAttack;
	friend class UBTTask_BountyHunterPlaceTrap;
	friend class UBTTask_BountyHunterReturnToIdle;
};