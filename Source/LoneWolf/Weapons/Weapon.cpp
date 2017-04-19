// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "Weapon.h"
#include "Character/PlayerCharacter/CharacterController.h"


AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	TimeSinceLastFire = 0.f;
	RateOfFire = 1.3f;
}

void AWeapon::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );

	TimeSinceLastFire += DeltaSeconds;
}

void AWeapon::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);
	OwningActor = NewOwner;

	if (Cast<ACharacterController>(OwningActor))
	{
		bOwnedByPlayer = true;
		//UE_LOG(LogTemp, Display, TEXT("The cast was a success"));
	}
}

bool AWeapon::Fire()
{
	if (TimeSinceLastFire >= RateOfFire)
	{
		//UE_LOG(LogTemp, Display, TEXT("Trying to call fire on a base class weapon."));
		TimeSinceLastFire = 0.f;
		return true;
	}
	return false;
}

bool AWeapon::AltFire()
{
	if (TimeSinceLastFire >= RateOfFire)
	{
		TimeSinceLastFire = 0.f;
		return true;
	}
	return false;
}

bool AWeapon::CanFire()
{
	return TimeSinceLastFire >= RateOfFire;
}

