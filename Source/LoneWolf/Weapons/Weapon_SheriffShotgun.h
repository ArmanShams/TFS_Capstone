// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapons/Weapon_Ranged.h"
#include "Weapon_SheriffShotgun.generated.h"

UCLASS()
class LONEWOLF_API AWeapon_SheriffShotgun : public AWeapon_Ranged
{
	GENERATED_BODY()
	
public:
	AWeapon_SheriffShotgun();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual bool Fire() override;
	virtual bool AltFire() override;
	virtual void Reload() override;
	virtual void SetOwner(AActor* NewOwner) override;
	virtual bool CanFire() override;
	virtual bool HasAmmo() override;
	virtual bool CanReload() override;
	virtual bool TwoShotsStart();
	virtual void TwoShotsEnd();

	UPROPERTY(EditDefaultsOnly)
	float AutoAttackInterval;

private:
	bool bAutoAttack;
};
