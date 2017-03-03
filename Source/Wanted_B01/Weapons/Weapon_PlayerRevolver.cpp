// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "Weapon_PlayerRevolver.h"




AWeapon_PlayerRevolver::AWeapon_PlayerRevolver()
{

}

void AWeapon_PlayerRevolver::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = 6;
	RateOfFire = 0.3f;
	MagazineCapacity = 6;

	MAXIMUM_TOTAL_AMMO = 0;
	TotalAmmo = MAXIMUM_TOTAL_AMMO;
}

void AWeapon_PlayerRevolver::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool AWeapon_PlayerRevolver::Fire()
{
	if (Super::Fire())
	{
		return true;
	}

	return false;
}

void AWeapon_PlayerRevolver::Reload()
{
	Super::Reload();
}
