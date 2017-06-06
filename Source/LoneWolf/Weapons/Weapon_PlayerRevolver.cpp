// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "Weapon_PlayerRevolver.h"



AWeapon_PlayerRevolver::AWeapon_PlayerRevolver()
{
	PrimaryActorTick.bCanEverTick = true;

	//MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	//MeshComponent->SetupAttachment(RootComponent);

	ConstructorHelpers::FClassFinder<AProjectile> ProjectileAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/ProjectileBP.ProjectileBP_C'"));
	if (ProjectileAsset.Class)
	{
		ProjectileToFire = (UClass*)ProjectileAsset.Class;
	}
	FanFireDeviationMultiplier = 2.2f;
}

void AWeapon_PlayerRevolver::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = 6;
	RateOfFire = 0.3f;
	MagazineCapacity = 6;
	DamagePerAttack = 10.f;

	MAXIMUM_TOTAL_AMMO = 0;
	TotalAmmo = MAXIMUM_TOTAL_AMMO;

	FanFireInterval = 0.1f; 
	ProjectileDeviationBase = ProjectileDeviation;
	FanFireDeviation = ProjectileDeviation * FanFireDeviationMultiplier;

	bFanFiring = false;
}

void AWeapon_PlayerRevolver::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bFanFiring)
	{
		if (Fire())
		{
			TimeSinceLastFire = RateOfFire - FanFireInterval;
		}
	}
}

bool AWeapon_PlayerRevolver::Fire()
{
	if (Super::Fire())
	{
		if (!bFanFiring)
		{
			ProjectileDeviation = ProjectileDeviationBase;
		}
		return true;
	}
	return false;
}

bool AWeapon_PlayerRevolver::AltFire()
{
	TimeSinceLastFire = RateOfFire;
	//if (Super::AltFire())
	{
		bFanFiring = true;
		ProjectileDeviation = FanFireDeviation;
		return true;
	}
	
	return false;
}

void AWeapon_PlayerRevolver::Reload()
{
	Super::Reload();
	ProjectileDeviation = ProjectileDeviationBase;
	bFanFiring = false;
}

void AWeapon_PlayerRevolver::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);
}

bool AWeapon_PlayerRevolver::CanFire()
{
	return Super::CanFire();
}

bool AWeapon_PlayerRevolver::HasAmmo()
{
	return Super::HasAmmo();
}

bool AWeapon_PlayerRevolver::CanReload()
{
	return Super::CanReload();
}

bool AWeapon_PlayerRevolver::IsFanFiring()
{
	return bFanFiring;
}

void AWeapon_PlayerRevolver::StopFanFire()
{
	bFanFiring = false;
}

