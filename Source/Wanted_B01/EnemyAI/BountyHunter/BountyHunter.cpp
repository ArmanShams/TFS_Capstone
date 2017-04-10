// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "Environment/BearTrap.h"
#include "BountyHunter.h"
#include "Engine.h"

ABountyHunter::ABountyHunter()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = GetCapsuleComponent();
	GetMesh()->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABountyHunter::OnActorBeginOverlap);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	Health = MAXHEALTH;
	MoveSpeed = .01f;
	TurnRate = 0.25f;
	MaxRange = 300.0f;
	AttackFrequency = 1.f;
	AttackRange = 300.0f;
	MaximumTrapsAllowed = 2;

	ConstructorHelpers::FClassFinder<AWeapon>WeaponAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/Weapon_RifleBP.Weapon_RifleBP_C'"));
	if (WeaponAsset.Class)
	{
		DefaultWeapon = (UClass*)WeaponAsset.Class;
	}
	//TrapArray = new TArray<AActor*>();
	//TrapArray.SetNum(2);

	ConstructorHelpers::FClassFinder<ABearTrap>TrapAsset(TEXT("Blueprint'/Game/Blueprints/Enemies/BountyHunter/BearTrapBP.BearTrapBP_C'"));
	if (TrapAsset.Class)
	{
		BearTrapClass = (UClass*)TrapAsset.Class;
	}
}

void ABountyHunter::BeginPlay()
{
	Super::BeginPlay();
	SetBearTrap();
}

void ABountyHunter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsInRange())
	{
		BasicAttack();
	}

}

float ABountyHunter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

bool ABountyHunter::bIsInRange()
{
	return Super::bIsInRange(AttackRange);
}

bool ABountyHunter::bIsInRange(float OveriddenDesiredRange)
{
	return Super::bIsInRange(OveriddenDesiredRange);
}

void ABountyHunter::BasicAttack()
{
	CurrentlyEquippedWeapon->Fire();
}

void ABountyHunter::SetBearTrap()
{
	if (BearTrapClass != NULL)
	{
		if (TrapArray.Num() >= MaximumTrapsAllowed)
		{
			AActor* TrapToDelete = TrapArray.Pop();
			TrapToDelete->SetLifeSpan(0.1f);

			UE_LOG(LogTemp, Display, TEXT("POP"));
		}
		BearTrapPlaced = GetWorld()->SpawnActor<ABearTrap>(BearTrapClass);
		BearTrapPlaced->SetActorRelativeLocation(GetMesh()->GetSocketLocation("RightToe_End"));
		// BearTrapPlaced->SetLifeSpan();
		TrapArray.Add(BearTrapPlaced);
		UE_LOG(LogTemp, Display, TEXT("Bounty Hunter set a bear trap, trap added to array list"));
	}

}

void ABountyHunter::RemoveBearTrap()
{
	TrapArray.Pop();
}

void ABountyHunter::OnActorBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{ 
//	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
			SetBearTrap();
	}
}

void ABountyHunter::EquipWeapon(TSubclassOf<AWeapon> WeaponToEquip)
{
	Super::EquipWeapon(WeaponToEquip);
	CurrentlyEquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("RightHand"));
	CurrentlyEquippedWeapon->SetActorRelativeRotation(FRotator(180.f, 180.f, 0.f));

}

