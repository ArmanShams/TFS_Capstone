// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "Weapon_Ranged.h"
#include "Weapons/Projectile.h"


// Sets default values
AWeapon_Ranged::AWeapon_Ranged()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FClassFinder<AProjectile> ProjectileAsset(TEXT("Blueprint'/Game/Blueprints/Enemies/ProjectileBP.ProjectileBP_C'"));
	if (ProjectileAsset.Class)
	{
		ProjectileToFire = (UClass*)ProjectileAsset.Class;
	}


}

// Called when the game starts or when spawned
void AWeapon_Ranged::BeginPlay()
{
	Super::BeginPlay();

	
	UE_LOG(LogTemp, Display, TEXT("ProjectileSpawnLocation: %s"), *MeshComponent->GetSocketRotation(FName("BarrelSocket")).ToString());


	//MeshComponent->SetStaticMesh(Mesh);
	
	/*
	CurrentAmmo = 0;
	RateOfFire = 0.3f;
	MagazineCapacity = 6;

	MAXIMUM_TOTAL_AMMO = 24;
	TotalAmmo = MAXIMUM_TOTAL_AMMO;
	*/
}

// Called every frame
void AWeapon_Ranged::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );

	//UE_LOG(LogTemp, Display, TEXT("%d"), TimeSinceLastFire);
}

bool AWeapon_Ranged::Fire()
{
	UE_LOG(LogTemp, Display, TEXT("Current ammo: %u"), CurrentAmmo);

	if (Super::Fire())
	{
		if (CurrentAmmo > 0)
		{
			CurrentAmmo--;
			
			if (MeshComponent->GetSocketByName(FName("BarrelSocket")))
			{
				AProjectile* Temp = GetWorld()->SpawnActor<AProjectile>(ProjectileToFire, MeshComponent->GetSocketLocation(FName("BarrelSocket")), MeshComponent->GetSocketRotation(FName("BarrelSocket")));
				Temp->Damage = DamagePerAttack;

				if (bOwnedByPlayer)
				{
					Temp->CollisionComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("A weapon's static mesh doesn't have a 'BarrelSocket' socket. Please add one"));
			}

			//UE_LOG(LogTemp, Display, TEXT("Rate of fire: %f"), RateOfFire);
			UE_LOG(LogTemp, Display, TEXT("Calling Fire on a ranged weapon"));
			UE_LOG(LogTemp, Display, TEXT("Current ammo after firing: %u"), CurrentAmmo);

		}
		if (CurrentAmmo == 0)
		{
			UE_LOG(LogTemp, Display, TEXT("Ran out of ammo after firing"));
			Reload();
		}
		return true;
	}
	if (CurrentAmmo == 0)
	{
		Reload();
	}
	return false;
}

bool AWeapon_Ranged::AltFire()
{
	if (Super::AltFire())
	{
		return true;
	}
	return false;
}

void AWeapon_Ranged::Reload()
{
	UE_LOG(LogTemp, Display, TEXT("Reloading"));
	if (MAXIMUM_TOTAL_AMMO != 0)
	{
		int8 AmmoNeededToFillMagazine = MagazineCapacity - CurrentAmmo;
		int8 NewTotalAmmo = TotalAmmo - AmmoNeededToFillMagazine;
		uint8 NewCurrentAmmo = CurrentAmmo + AmmoNeededToFillMagazine;
		
		if (NewTotalAmmo < 0)
		{
			NewCurrentAmmo += NewTotalAmmo;
			NewTotalAmmo += -NewTotalAmmo;
		}

		CurrentAmmo = NewCurrentAmmo;
		TotalAmmo = NewTotalAmmo;

		UE_LOG(LogTemp, Display, TEXT("Ammo To Add: %i"), AmmoNeededToFillMagazine);
		UE_LOG(LogTemp, Display, TEXT("Current ammo: %u"), CurrentAmmo);
		UE_LOG(LogTemp, Display, TEXT("Total ammo: %i"), TotalAmmo);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Weapon has infinite reserve ammo"));
		CurrentAmmo = MagazineCapacity;
	}
	
	
}

