// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "Weapons/Weapon_Ranged.h"
#include "RangedAI.h"


ARangedAI::ARangedAI()
{
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = GetMesh();
	
	// Weapon Socket
	const USkeletalMeshSocket* GunSocket;
	GunSocket = GetMesh()->GetSocketByName(FName("Gun"));
	FName GunFName = GunSocket->GetFName();

	
	Health = MAXHEALTH;
	
	ConstructorHelpers::FClassFinder<AWeapon>WeaponAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/Weapon_RifleBP.Weapon_RifleBP_C'"));
	if (WeaponAsset.Class)
	{
		
		DefaultWeaponClass = (UClass*)WeaponAsset.Class;
	}
}

float ARangedAI::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float NewHealth = Health;
	NewHealth -= DamageAmount;

	if (NewHealth > MAXHEALTH)
	{
		NewHealth = MAXHEALTH;
	}

	UE_LOG(LogTemp, Display, TEXT("Player health modified, health is now: %f"), Health);

	Health = NewHealth;

	if (NewHealth <= 0.f)
	{
		CurrentlyEquippedWeapon->SetLifeSpan(0.1f);
		SetLifeSpan(0.1f);
	}

	return Health;
}




void ARangedAI::BeginPlay()
{
	Super::BeginPlay();

	if (DefaultWeaponClass != NULL)
	{
		UE_LOG(LogTemp, Display, TEXT("Enemy Equipped Rifle"));
		CurrentlyEquippedWeapon = GetWorld()->SpawnActor<AWeapon>(DefaultWeaponClass);
		CurrentlyEquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("RightHand"));
		CurrentlyEquippedWeapon->SetActorRelativeRotation(FRotator(0.f, 270.f, 0.f));

	}
}

void ARangedAI::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );


	//CurrentlyEquippedWeapon->Fire();

	// FVector::Dist(this->GetComponentLocation(), PlayerReference->GetWorldLocation());
}
