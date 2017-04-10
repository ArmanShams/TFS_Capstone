// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyAI/Enemy.h"
#include "BountyHunter.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_B01_API ABountyHunter : public AEnemy
{
	GENERATED_BODY()

public:
	ABountyHunter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual bool bIsInRange() override;
	virtual bool bIsInRange(float OveriddenDesiredRange) override;

private:
	void BasicAttack();

	UFUNCTION()
	void SetBearTrap();

	UFUNCTION()
	void OnActorBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditDefaultsOnly)
	uint8 MaximumTrapsAllowed;

	TSubclassOf<class ABearTrap> BearTrapClass;
	ABearTrap* BearTrapPlaced;

	TArray<AActor*> TrapArray;

	virtual void EquipWeapon(TSubclassOf<AWeapon> WeaponToEquip);

	friend class ABearTrap;
};