// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BartenderAI.h"
#include "Weapons/Projectile.h"

ABartenderAI::ABartenderAI()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Health = MAXHEALTH;

	MoveSpeed = .04f;

	TurnRate = 0.25f;

	MaxRange = 100.0f;

	AttackFrequency = 5.f;

	AttackRange = 250.0f;
	
}

void ABartenderAI::BeginPlay()
{
	Super::BeginPlay();
}

void ABartenderAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);



}

void ABartenderAI::SetupPlayerInputComponent(class UInputComponent* InInputComponent)
{
	Super::SetupPlayerInputComponent(InInputComponent);
}

void ABartenderAI::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::AddStatusEffect(ClassToCreateFrom, bShouldPerformTickAction, LifeTime, TickRate, CharacterThatInflictedStatusEffect);
}

void ABartenderAI::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, bool bShouldDealDamage, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::AddStatusEffect(ClassToCreateFrom, bShouldPerformTickAction, bShouldDealDamage, LifeTime, DamageToDeal, TickRate, CharacterThatInflictedStatusEffect);
}

float ABartenderAI::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

bool ABartenderAI::bIsInRange()
{
	return Super::bIsInRange(AttackRange);
}

bool ABartenderAI::bIsInRange(float OveriddenDesiredRange)
{
	return Super::bIsInRange(OveriddenDesiredRange);
}

AWeapon* ABartenderAI::GetEquippedWeapon()
{
	return Super::GetEquippedWeapon();
}

bool ABartenderAI::bIsSoftCC()
{
	return Super::bIsSoftCC();
}

bool ABartenderAI::bIsHardCC()
{
	return Super::bIsHardCC();
}

CharacterState::StatusEffect ABartenderAI::GetStatusEffect()
{
	return Super::GetStatusEffect();
}

void ABartenderAI::Destroyed()
{
	Super::Destroyed();
}

AWeapon* ABartenderAI::EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip)
{
	CurrentlyEquippedWeapon = Super::EquipNewWeapon(WeaponToEquip);
	return CurrentlyEquippedWeapon;
}

FVector ABartenderAI::HitTargetLocationAtTime(FVector StartPosition, FVector TargetPosition, FVector GravityBase, float TimeToTarget)
{
	FVector AtoB = TargetPosition - StartPosition;
	FVector Horizontal = GetHorizontalVector(AtoB, GravityBase);
	float HorizontalDistance = Horizontal.Size();
	FVector Vertical = GetVerticalVector(AtoB, GravityBase);
	float VerticalDistance = Vertical.Size() * Sign(FVector::DotProduct(Vertical, -GravityBase));

	float HorizontalSpeed = HorizontalDistance / TimeToTarget;
	float VerticalSpeed = (VerticalDistance + ((0.5f * GravityBase.Size()) * (TimeToTarget * TimeToTarget))) / TimeToTarget;
	//if (Horizontal.Normalize() && GravityBase.Normalize())
	{
		FVector Launch = (Horizontal.GetSafeNormal() * HorizontalSpeed) - (GravityBase.GetSafeNormal() * VerticalSpeed);
		return Launch;
	}
	return FVector::ZeroVector;
}

FVector ABartenderAI::GetHorizontalVector(FVector Direction, FVector GravityBase)
{
	FVector Output;
	FVector Perpendicular = FVector::CrossProduct(Direction, GravityBase);
	Perpendicular = FVector::CrossProduct(GravityBase, Perpendicular);
	Output = Direction.ProjectOnTo(Perpendicular); //FVector::Pro(Direction, Perpendicular);
	return Output;
}

FVector ABartenderAI::GetVerticalVector(FVector Direction, FVector GravityBase)
{
	FVector Output;
	//output = FVector.Project(AtoB, gravityBase);
	Output = Direction.ProjectOnTo(GravityBase);
	return Output;
}

float ABartenderAI::Sign(float RetrieveSignOf)
{
	if (RetrieveSignOf < 0)
	{
		return -1.f;
	}
	if (RetrieveSignOf > 0)
	{
		return 1.0f;
	}
	return 0;
}

