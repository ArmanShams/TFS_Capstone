// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapons/Weapon.h"
#include "EnemyMelee.generated.h"

UCLASS()
class WANTED_B01_API AEnemyMelee : public AWeapon
{
	GENERATED_BODY()

public:
	AEnemyMelee();
	virtual void Fire() override;

protected:
	UPROPERTY(VisibleAnywhere)
		class UMeshComponent* Knife;


	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* Collider;

	UPROPERTY(EditDefaultsOnly)
		float Damage;
	
	bool bIsSwinging;

private:
	UFUNCTION()
		void OnMeleeWeaponOverlapBegin(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void OnMeleeWeaponHit(AActor* HitActor);
};

