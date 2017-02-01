// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapons/Weapon.h"
#include "Weapon_Ranged.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_B01_API AWeapon_Ranged : public AWeapon
{
	GENERATED_BODY()
	
public:
	virtual void Fire() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ProjectileClass;
	
	
};
