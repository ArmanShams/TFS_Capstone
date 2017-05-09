// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapons/Weapon_Ranged.h"
#include "Weapon_PlayerRevolver.generated.h"

/**
 * 
 */
UCLASS()
class LONEWOLF_API AWeapon_PlayerRevolver : public AWeapon_Ranged
{
	GENERATED_BODY()

public:
	AWeapon_PlayerRevolver();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual bool Fire() override;
	virtual bool AltFire() override;
	virtual void Reload() override;	
	virtual void SetOwner(AActor* NewOwner) override;
	virtual bool CanFire() override;
	virtual bool HasAmmo() override;
	virtual bool CanReload() override;
	virtual bool IsFanFiring();

	UPROPERTY(EditDefaultsOnly)
	float FanFireInterval;

private:
	bool bFanFiring;

	
};
