// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "Weapon_SheriffShotgun.h"

AWeapon_SheriffShotgun::AWeapon_SheriffShotgun()
{
	ConstructorHelpers::FClassFinder<AProjectile> ProjectileAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/ProjectileBP.ProjectileBP_C'"));
	if (ProjectileAsset.Class)
	{
		ProjectileToFire = (UClass*)ProjectileAsset.Class;
	}
}

void AWeapon_SheriffShotgun::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = 2;
	RateOfFire = 0.3f;
	MagazineCapacity = 2;
	DamagePerAttack = 10.f;

	MAXIMUM_TOTAL_AMMO = 0;
	TotalAmmo = MAXIMUM_TOTAL_AMMO;

	AutoAttackInterval = 0.1f;
	bAutoAttack = false;
}

void AWeapon_SheriffShotgun::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (bAutoAttack)
	{
		if (Fire())
		{
			TimeSinceLastFire = RateOfFire - AutoAttackInterval;
		}
	}
}

bool AWeapon_SheriffShotgun::Fire()
{
	if (Super::Fire())
	{
		return true;
	}
	return false;
}

bool AWeapon_SheriffShotgun::AltFire()
{
	if (Super::AltFire())
	{
		UE_LOG(LogTemp, Display, TEXT("ALTFIRING BUT ONLY AT AN APPROPRIATE SPEED"));
		TimeSinceLastFire = RateOfFire;

		bAutoAttack = true;
		return true;
	}
	return false;
}

void AWeapon_SheriffShotgun::Reload()
{
	Super::Reload();
	bAutoAttack = false;
}

void AWeapon_SheriffShotgun::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);
}

bool AWeapon_SheriffShotgun::CanFire()
{
	return Super::CanFire();
}

bool AWeapon_SheriffShotgun::HasAmmo()
{
	return Super::HasAmmo();
}

bool AWeapon_SheriffShotgun::CanReload()
{
	return Super::CanReload();
}

bool AWeapon_SheriffShotgun::TwoShotsStart()
{
	return bAutoAttack;
}

void AWeapon_SheriffShotgun::TwoShotsEnd()
{
	bAutoAttack = false;
}
