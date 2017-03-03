// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "Weapon.h"


// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	LastFired = MAX_FLT;

}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LastFired += DeltaTime;

	if (CanFire())
	{
		Fire();
	}

}

void AWeapon::BeginFire()
{
	bIsFiring = true;
}

void AWeapon::Fire()
{
	LastFired = 0.f;
}

void AWeapon::EndFire()
{
	bIsFiring = false;
}

bool AWeapon::CanFire()
{
	return bIsFiring && LastFired >= RateOfFire;
}