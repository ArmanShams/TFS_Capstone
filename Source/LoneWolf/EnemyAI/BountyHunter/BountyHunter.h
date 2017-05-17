// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyAI/Enemy.h"
#include "BountyHunter.generated.h"

UENUM(BlueprintType)
enum class BountyHunterState : uint8
{
	IDLE			UMETA(DisplayName = "Idle"),
	READYINGATTACK	UMETA(DisplayName = "PreparingToAttack"),
	AIMING			UMETA(DisplayName = "Aiming"),
	ATTACKING		UMETA(DisplayName = "Attacking"),
	FLEEING			UMETA(DisplayName = "Fleeing"),
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
	virtual void SetBountyHunterState(BountyHunterState NewState);

protected:
	virtual bool bIsSoftCC() override;
	virtual bool bIsHardCC() override;
	virtual AWeapon* EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip) override;

	UFUNCTION()
	void SetBearTrap(ATrapLocations* NewTrapLocation, const FHitResult & SweepResult);

	UFUNCTION()
	void OnActorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void Attack();

	bool bPlayRecoilAnimation;
	bool bCanTriggerFireAnimation;

	UPROPERTY(EditDefaultsOnly)
	uint8 MaximumTrapsAllowed;

	FVector PositionToMove;

	TSubclassOf<class ABearTrap> BearTrapClass;
	ABearTrap* BearTrapPlaced;

	TArray<AActor*> TrapArray;
	BountyHunterState CurrentState;

	bool bPlayBearTrapAnimation;

	friend class ABearTrap;
	friend class UBTTask_BountyHunterAttack;
	friend class UBountyHunterAnimInstance;
};