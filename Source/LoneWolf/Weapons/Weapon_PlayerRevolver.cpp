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
		return true;
	}

	return false;
}

bool AWeapon_PlayerRevolver::AltFire()
{
	if (Super::AltFire())
	{
		UE_LOG(LogTemp, Display, TEXT("ALTFIRING BUT ONLY AT AN APPROPRIATE SPEED"));
		TimeSinceLastFire = RateOfFire;

		bFanFiring = true;
		return true;
	}
	return false;
}

void AWeapon_PlayerRevolver::Reload()
{
	Super::Reload();
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

