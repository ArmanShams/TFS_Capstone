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
	TimeSinceLastFire = 0.f;
	RateOfFire = 1.3f;
}

// Called every frame
void AWeapon::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );

//	UE_LOG(LogTemp, Display, TEXT("Beam"));
	TimeSinceLastFire += DeltaSeconds;

}


bool AWeapon::Fire()
{
	if (TimeSinceLastFire > RateOfFire)
	{
		UE_LOG(LogTemp, Display, TEXT("Trying to call fire on a base class weapon."));
		TimeSinceLastFire = 0.f;
		return true;
	}
	return false;
}

