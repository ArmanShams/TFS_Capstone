// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapons/Weapon.h"
#include "Weapon_Melee.generated.h"

/**
 * 
 */
UCLASS()
class LONEWOLF_API AWeapon_Melee : public AWeapon
{
	GENERATED_BODY()
	
public:
	AWeapon_Melee();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetOwner(AActor* NewOwner) override;

	virtual bool Fire() override;

	virtual bool Fire(UAttackTypes::MeleeAttackType NewAttackType);

	virtual bool AltFire() override;

	virtual bool AltFire(UAttackTypes::MeleeAttackType NewAttackType);

	virtual void SetAttackType(UAttackTypes::MeleeAttackType NewAttackType);

	virtual void ToggleCollider();

	UPROPERTY(EditDefaultsOnly)
	bool bMultiTap;

	bool bHasHit;

protected:
	UFUNCTION()
	void OnMeleeWeaponOverlapBegin(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class UCapsuleComponent* CapsuleComponent;

	UAttackTypes::MeleeAttackType AttackType;

	FName CollisionProfileName;

	bool bCollisionEnabled;

	

};
