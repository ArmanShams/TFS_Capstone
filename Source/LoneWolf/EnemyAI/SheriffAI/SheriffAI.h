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
	
	virtual AWeapon* GetEquippedWeapon();
	
	virtual bool bIsInRange();
	virtual bool bIsInRange(float OveriddenDesiredRange);
	virtual bool bIsSoftCC() override;
	virtual bool bIsHardCC() override;
	virtual void Destroyed() override;

	SheriffState CurrentState;
	virtual SheriffState GetSheriffState();
	virtual void SetSheriffState(SheriffState NewStateToEnter);

	void Lasso();

	FComponentReference CastedPlayerReference;

	UPROPERTY(EditAnywhere)
	class UCableComponent* LassoCableComponent;
	
	AActor* LassoActor;
	TSubclassOf<AActor> LassoActorClass;

protected:
	virtual AWeapon* EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip) override;

	friend class USheriffAnimInstance;
};
 