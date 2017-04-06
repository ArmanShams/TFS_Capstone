// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyAI/Enemy.h"
#include "MinerAI.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class MinerState : uint8
{
	IDLE			UMETA(DisplayName = "Idle"),
	READYING		UMETA(DisplayName = "PreparingCharge"),
	CHARGING		UMETA(DisplayName = "Charging"),
	ATTACKING		UMETA(DisplayName = "Attacking")
};

UCLASS(Blueprintable)
class WANTED_B01_API AMinerAI : public AEnemy
{
	GENERATED_BODY()
	
public:
	AMinerAI();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual bool bIsInRange() override;
	virtual bool bIsInRange(float OveriddenDesiredRange) override;
	virtual AWeapon* GetEquippedWeapon() override;
	virtual bool bIsSoftCC() override;
	virtual bool bIsHardCC() override;
	virtual bool GetBTIsInRange();
	virtual MinerState GetMinerState();
	virtual CharacterState::StatusEffect GetStatusEffect() override;

	// The distance the Miner will be able to use the Charge, not the length of the charge itself.
	UPROPERTY(EditDefaultsOnly)
	float DistanceToUseCharge;
	
	// The offset from the Miner where the visual telegraph for the charge will spawn.
	UPROPERTY(EditDefaultsOnly)
	float ArrowSpawnOffset;

	UPROPERTY(EditDefaultsOnly)
	float ChargeSpeed;

	UPROPERTY(EditDefaultsOnly)
	float ChargeDamage;

	AActor* ArrowDecalActor;
	TSubclassOf<AActor> ArrowDecalClass;

protected:
	float TimeSinceLastCharge;
	virtual void EquipWeapon(TSubclassOf<AWeapon> WeaponToEquip) override;
	virtual void StartCharge();
	virtual void Charge();
	virtual void SetStatusEffect(CharacterState::StatusEffect NewStatusEffect) override;
	virtual void SetMinerState(MinerState NewStateToEnter);
	virtual void Attack();

	UFUNCTION()
	virtual void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);



	MinerState CurrentState;

	friend class UMinerAnimInstance;
	friend class UBTTask_MinerStartCharge;
	friend class UBTTask_MinerCharge;
	friend class UBTTask_MinerAttack;
	friend class UBTTask_MinerReturnToIdle;
};
