// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyAI/Enemy.h"
#include "BountyHunter.generated.h"

UENUM(BlueprintType)
enum class BounterHunterState : uint8
{
	IDLE			UMETA(DisplayName = "Idle"),
	READYINGATTACK	UMETA(DisplayName = "PreparingToAttack"),
	ATTACKING		UMETA(DisplayName = "Attacking"),
	SETTINGTRAP		UMETA(DisplayName = "PlacingTrap")
};

UCLASS(Blueprintable)
class LONEWOLF_API ABountyHunter : public AEnemy
{
	GENERATED_BODY()

public:
	ABountyHunter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InInputComponent) override;
	virtual void AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect) override;
	virtual void AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, bool bShouldDealDamage, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect) override;
	virtual AWeapon* GetEquippedWeapon() override;
	virtual bool bIsInRange() override;
	virtual bool bIsInRange(float OveriddenDesiredRange) override;
	virtual bool GetbIsInHardCC() override;
	virtual bool GetbIsInSoftCC() override;
	virtual void Destroyed() override;
	virtual bool bCanTriggerRecoilAnimation();
	virtual void SetBountyHunterState(BounterHunterState NewState);

protected:
	virtual bool bIsSoftCC() override;			// Returns true if the actor's Status Effects is a 'softCC'. Defined in Design Document
	virtual bool bIsHardCC() override;			// Returns true if the actor's Status Effects is a 'hardCC'. Defined in Design Document
	virtual AWeapon* EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip) override;

	UFUNCTION()
	void SetBearTrap(ATrapLocations* NewTrapLocation, const FHitResult & SweepResult);

	UFUNCTION()
	void OnActorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly)
		uint8 MaximumTrapsAllowed;

	bool bPlayRecoilAnimation;

	virtual void Attack();

	virtual void EquipWeapon(TSubclassOf<AWeapon> WeaponToEquip);

	TSubclassOf<class ABearTrap> BearTrapClass;
	ABearTrap* BearTrapPlaced;

	TArray<AActor*> TrapArray;
	BounterHunterState CurrentState;

	friend class ABearTrap;
	friend class UBountyHunterAnimInstance;
	friend class UBTTask_BountyHunterAttack;
	friend class UBTTask_BountyHunterPlaceTrap;
};