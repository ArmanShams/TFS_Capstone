// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "BartenderAI.h"

ABartenderAI::ABartenderAI()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Health = MAXHEALTH;

	MoveSpeed = .04f;

	TurnRate = 0.25f;

	MaxRange = 100.0f;

	AttackFrequency = 5.f;

	AttackRange = 150.0f;

	KegRollCooldown = 12.0f;

	FireBreathCooldown = 12.0f;

	TimeSinceLastFB = FireBreathCooldown;

	TimeSinceLastKR = KegRollCooldown;

	DistanceToUseFB = 1500.f;

	DistanceToUseKegRoll = 1500.f;

	FireDOT = 5.f;

	// Replace with new weapon asset for respective enemy type.
	//ConstructorHelpers::FClassFinder<AWeapon>WeaponAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/KnifeBP_Arman.KnifeBP_Arman_C'"));

	//if (WeaponAsset.Class)
	//{
	//	UE_LOG(LogTemp, Display, TEXT("WE HAVE FOUND THE CLASS"));
	//	DefaultWeapon = (UClass*)WeaponAsset.Class;
	//}
}

void ABartenderAI::BeginPlay()
{
	Super::BeginPlay();
}

void ABartenderAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (TimeSinceLastFB <= FireBreathCooldown)
	{
		TimeSinceLastFB += DeltaSeconds;
	}

	if (TimeSinceLastKR <= KegRollCooldown)
	{
		TimeSinceLastKR += DeltaSeconds;
	}
	
	if (TimeSinceLastFB >= FireBreathCooldown && bIsInRange(DistanceToUseFB))
	{
		UE_LOG(LogTemp, Display, TEXT("A bartender is in range to use Fire Breath."));
	}

	if (TimeSinceLastKR >= KegRollCooldown && bIsInRange(DistanceToUseKegRoll))
	{
		UE_LOG(LogTemp, Display, TEXT("A bartender is in range to use Keg Roll."));
	}
}

void ABartenderAI::SetupPlayerInputComponent(UInputComponent * InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

float ABartenderAI::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

bool ABartenderAI::bIsInRange()
{
	return Super::bIsInRange();
}

bool ABartenderAI::bIsInRange(float OveriddenDesiredRange)
{
	return Super::bIsInRange(OveriddenDesiredRange);
}

float ABartenderAI::DamageOverTime(float FireDOT)
{
	return FireDOT;
}
