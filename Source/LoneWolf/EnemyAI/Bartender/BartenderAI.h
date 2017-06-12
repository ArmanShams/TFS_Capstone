// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyAI/Enemy.h"
#include "BartenderAI.generated.h"


UCLASS()
class LONEWOLF_API ABartenderAI : public AEnemy
{
	GENERATED_BODY()

public:
	ABartenderAI();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	virtual void AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect) override;
	virtual void AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, bool bShouldDealDamage, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual bool bIsInRange() override;
	virtual bool bIsInRange(float OveriddenDesiredRange) override;
	virtual AWeapon* GetEquippedWeapon() override;
	virtual bool bIsSoftCC() override;
	virtual bool bIsHardCC() override;


	virtual CharacterState::StatusEffect GetStatusEffect() override;
	virtual void Destroyed() override;


	virtual void ThrowMolotov();
	virtual void RollKeg();
	virtual bool GetIsAttacking();
	virtual void SetIsAttacking(bool NewValue);

protected:
	virtual void Die() override;
	virtual AWeapon* EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip) override;

	virtual FVector HitTargetLocationAtTime(FVector StartPosition, FVector TargetPosition, FVector GravityBase, float TimeToTarget);
	virtual FVector GetHorizontalVector(FVector Direction, FVector GravityBase);
	virtual FVector GetVerticalVector(FVector Direction, FVector GravityBase);

	virtual float Sign(float RetrieveSignOf);

	UPROPERTY(EditDefaultsOnly, Category = "Molotov")
	float TimeForMolotovToReachTargetLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Molotov")
	float CushionSpace;

	UPROPERTY(EditDefaultsOnly, Category = "Molotov")
	float DecalLifeTime;

	UPROPERTY(EditDefaultsOnly, Category = "Molotov")
	AActor* MolotovDecalActor;
	UPROPERTY(EditDefaultsOnly, Category = "Molotov")
	TSubclassOf<AActor> MolotovActorClass;

	//Blackboard booleans to check range
	bool bAttack;
	bool bFlee;

	bool bSpawned = false;
	bool bIsAttacking;

	friend class UBartenderAIAnimInstance;
	friend class UBTTask_BountyHunterAttack;
	friend class UBTTask_BartenderRollKeg;
};
