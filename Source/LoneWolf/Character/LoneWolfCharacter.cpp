// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "LoneWolfCharacter.h"


ALoneWolfCharacter::ALoneWolfCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bIsInHardCC = false;
	bIsInSoftCC = false;
	MoveSpeedBase = 0.4f;
	MoveSpeedActual = MoveSpeedBase;
}

void ALoneWolfCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALoneWolfCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bIsInHardCC = bIsHardCC();
	bIsInSoftCC = bIsSoftCC();
}

void ALoneWolfCharacter::SetupPlayerInputComponent(class UInputComponent* InInputComponent)
{
	Super::SetupPlayerInputComponent(InInputComponent);
}

float ALoneWolfCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	this->OnDamageTaken();
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}
/*
	Params
	ClassToCreateFrom					-The static class of an object that derives from UStatusEffectBase to create
	bShouldPerformTickAction			-Whether or not the status effect will perform an action every TickRate seconds
	LifeTime							-How long the status effect will last in seconds
	TickRate							-Every TickRate seconds, if bShouldPerformTickAction is true, the object will call it's ActionToPerformOnTick (For damage over times, how many times per second the damage is applied.
	CharacterThatInflictedStatusEffect	-The character that inflicted the status effect.
*/
void ALoneWolfCharacter::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	if (GetWorld()->HasBegunPlay())
	{
		UStatusEffectBase* Effect = NewObject<UStatusEffectBase>(this, ClassToCreateFrom);

		this->AddOwnedComponent(Effect);
		Effect->RegisterComponent();
		Effect->SetUpStatusEffect(false, bShouldPerformTickAction, LifeTime, TickRate, this, CharacterThatInflictedStatusEffect);
	}
}
/*
	Params
	ClassToCreateFrom					-The static class of an object that derives from UStatusEffectBase to create
	bShouldPerformTickAction			-Whether or not the status effect will perform an action every TickRate seconds
	bShouldDealDamage					-Whether or not this status effect will deal damage when it's tick action is performed.
	LifeTime							-How long the status effect will last in seconds
	DamageToDeal						-Amount of damage dealt to the actor inflicted by the status effect.
	TickRate							-Every TickRate seconds, if bShouldPerformTickAction is true, the object will call it's ActionToPerformOnTick (For damage over times, how many times per second the damage is applied.
	CharacterThatInflictedStatusEffect	-The character that inflicted the status effect.
*/
void ALoneWolfCharacter::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, bool bShouldDealDamage, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	if (GetWorld()->HasBegunPlay())
	{
		UStatusEffectBase* Effect = NewObject<UStatusEffectBase>(this, ClassToCreateFrom);

		this->AddOwnedComponent(Effect);
		Effect->RegisterComponent();
		Effect->SetUpStatusEffect(bShouldDealDamage, bShouldPerformTickAction, LifeTime, DamageToDeal, TickRate, this, CharacterThatInflictedStatusEffect);
	}
}

bool ALoneWolfCharacter::GetbIsInHardCC()
{
	return bIsInHardCC;
}

bool ALoneWolfCharacter::GetbIsInSoftCC()
{
	return bIsInSoftCC;
}

AWeapon* ALoneWolfCharacter::EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip)
{
	//Super::EquipNewWeapon(WeaponToEquip);
	CurrentlyEquippedWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponToEquip);
	CurrentlyEquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("hand_r"));
	CurrentlyEquippedWeapon->SetOwner(this);
	return CurrentlyEquippedWeapon;
	//CurrentlyEquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, FName("hand_r"));
	//CurrentlyEquippedWeapon->SetActorLocation(GetMesh()->GetSocketLocation(FName("hand_r")));		
	//CurrentlyEquippedWeapon->SetActorRotation(FRotator::ZeroRotator);
	
}

AWeapon* ALoneWolfCharacter::GetEquippedWeapon()
{
	if (CurrentlyEquippedWeapon != NULL)
	{
		return CurrentlyEquippedWeapon;
	}
	return NULL;
}

float ALoneWolfCharacter::GetHealthPercent()
{
	return Health / MAXHEALTH;
}

bool ALoneWolfCharacter::bIsHardCC()
{
	if (GetComponentByClass(UStatusEffect_HardCrowdControl::StaticClass()))
	{
		return true;
	}
	return false;
}

bool ALoneWolfCharacter::bIsSoftCC()
{
	if (bIsHardCC())
	{
		return true;
	}
	if (GetComponentByClass(UStatusEffect_SoftCrowdControl::StaticClass()))
	{
		return true;
	}
	return false;
}

void ALoneWolfCharacter::Die()
{
	OnDeath();
}

void ALoneWolfCharacter::Destroyed()
{
	Super::Destroyed();
}


