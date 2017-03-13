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

	ConstructorHelpers::FClassFinder<AWeapon_Ranged>WeaponAsset(TEXT("Blueprint'/Game/Blueprints/Enemies/RangedAI/Weapon_RifleBP.Weapon_RifleBP_C'"));
	if (WeaponAsset.Class)
	{
		UE_LOG(LogTemp, Display, TEXT("Enemy Equipped Rifle"));
		// RifleClass = (UClass*)WeaponAsset.Class;
	}
}

void ARangedAI::BeginPlay()
{
	Super::BeginPlay();
	OnFire();
}

void ARangedAI::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	// FVector::Dist(this->GetComponentLocation(), PlayerReference->GetWorldLocation());
}

void ARangedAI::OnFire()
{

}
