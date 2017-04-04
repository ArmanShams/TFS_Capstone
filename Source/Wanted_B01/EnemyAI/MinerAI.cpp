// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "MinerAI.h"


AMinerAI::AMinerAI()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Health = MAXHEALTH;

	MoveSpeed = .04f;

	TurnRate = 0.25f;

	MaxRange = 100.0f;

	AttackFrequency = 5.f;

	AttackRange = 150.0f;

	ChargeCooldown = 12.0f;

	TimeSinceLastCharge = ChargeCooldown;

	DistanceToUseCharge = 1500.f;

	// Replace with new weapon asset for respective enemy type.
	ConstructorHelpers::FClassFinder<AWeapon>WeaponAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/KnifeBP_Arman.KnifeBP_Arman_C'"));

	if (WeaponAsset.Class)
	{
		UE_LOG(LogTemp, Display, TEXT("WE HAVE FOUND THE CLASS"));
		DefaultWeapon = (UClass*)WeaponAsset.Class;
	}
}

void AMinerAI::BeginPlay()
{
	Super::BeginPlay();
}

void AMinerAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (TimeSinceLastCharge <= ChargeCooldown)
	{
		TimeSinceLastCharge += DeltaSeconds;
	}
	
	if (TimeSinceLastCharge >= ChargeCooldown && bIsInRange(DistanceToUseCharge))
	{
		UE_LOG(LogTemp, Display, TEXT("A miner is in range to use the charge."));
	}
}

void AMinerAI::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

float AMinerAI::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

bool AMinerAI::bIsInRange()
{
	return Super::bIsInRange();
}

bool AMinerAI::bIsInRange(float OveriddenDesiredRange)
{
	return Super::bIsInRange(OveriddenDesiredRange);
}

//void AMinerAI::EquipWeapon(TSubclassOf<AWeapon> WeaponToEquip)
//{
//	Super::EquipWeapon(WeaponToEquip);
//}
