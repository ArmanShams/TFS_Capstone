// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapons/Weapon.h"
#include "Weapon_Melee.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_B01_API AWeapon_Melee : public AWeapon
{
	GENERATED_BODY()

public:
	AWeapon_Melee();
	virtual void Fire() override;

protected:
	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* Collider;

	UPROPERTY(EditDefaultsOnly)
	float Damage;
	bool bIsSwinging;
	
private:
	UFUNCTION()
	void OnMeleeWeaponOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void OnMeleeWeaponHit(AActor* HitActor);

};
