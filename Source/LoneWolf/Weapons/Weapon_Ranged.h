// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapons/Weapon.h"
#include "Weapons/Projectile.h"
#include "Weapon_Ranged.generated.h"

UCLASS()
class LONEWOLF_API AWeapon_Ranged : public AWeapon
{
	GENERATED_BODY()


public:	
	AWeapon_Ranged();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual bool Fire() override;
	virtual bool AltFire() override;
	virtual void Reload();
	virtual void SetOwner(AActor* NewOwner) override;
	virtual bool CanFire() override;
	virtual bool HasAmmo();
	virtual bool CanReload();

protected:
	UPROPERTY(EditDefaultsOnly)
	float ProjectileDeviation;

	UPROPERTY(EditDefaultsOnly)
	uint8 MagazineCapacity;

	UPROPERTY(EditDefaultsOnly)
	uint8 MAXIMUM_TOTAL_AMMO;

	UPROPERTY(EditDefaultsOnly)
	uint8 CurrentAmmo;

	UPROPERTY(EditDefaultsOnly)
	int8 TotalAmmo;

	TSubclassOf<AProjectile> ProjectileToFire;
	
	friend class AProjectle;

	friend class UUIWidget;
};
