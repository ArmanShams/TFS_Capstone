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
class LONEWOLF_API AMinerAI : public AEnemy
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

	// The distance at which the Miner will be able to use the stomp;
	UPROPERTY(EditDefaultsOnly)
	float DistanceToUseStomp;
	// The damage dealt by the stomp;
	UPROPERTY(EditDefaultsOnly)
	float StompDamage;
	// Radius the stomp will apply damage in.
	UPROPERTY(EditDefaultsOnly)
	float StompRadius;
	//// Whether or not the damage dealt should dissipate based on the distance from the center point of the stomp.
	//UPROPERTY(EditDefaultsOnly)
	//bool bShouldRadialDamageFallOff;
	// The distance the Miner will be able to use the Charge, not the length of the charge itself.
	UPROPERTY(EditDefaultsOnly)
	float DistanceToUseCharge;
	// The offset from the Miner where the visual telegraph for the charge will spawn.
	UPROPERTY(EditDefaultsOnly)
	float ArrowSpawnOffset;
	// The speed at which the Miner will move while charging.
	UPROPERTY(EditDefaultsOnly)
	float ChargeSpeed;
	// The damage dealt by the charge
	UPROPERTY(EditDefaultsOnly)
	float ChargeDamage;
	// The distance objects struck by the charge will be launched.
	UPROPERTY(EditDefaultsOnly)
	float ChargeLaunchDistance;

	AActor* ArrowDecalActor;
	TSubclassOf<AActor> ArrowDecalClass;
	AActor* StompDecalActor;
	TSubclassOf<AActor> StompDecalActorClass;

protected:
	float DefaultMoveSpeed;

	virtual void EquipWeapon(TSubclassOf<AWeapon> WeaponToEquip) override;
	virtual void StartCharge();
	virtual void Charge();
	virtual void SetStatusEffect(CharacterState::StatusEffect NewStatusEffect) override;
	virtual void SetMinerState(MinerState NewStateToEnter);
	virtual void Attack();
	virtual void StartStomp();
	virtual void Stomp();

	UFUNCTION()
	virtual void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



	bool bChargeHasDamagedPlayer;

	MinerState CurrentState;

	friend class UMinerAnimInstance;
	friend class UBTTask_MinerStartCharge;
	friend class UBTTask_MinerCharge;
	friend class UBTTask_MinerAttack;
	friend class UBTTask_MinerReturnToIdle;
	friend class UBTTask_MinerStartStomp;
	friend class UBTTask_MinerStomp;
};
