// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "Weapon_Ranged.h"
#include "Weapons/Projectile.h"


// Sets default values
AWeapon_Ranged::AWeapon_Ranged()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FClassFinder<AProjectile> ProjectileAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/ProjectileBP.ProjectileBP_C'"));
	if (ProjectileAsset.Class)
	{
		ProjectileToFire = (UClass*)ProjectileAsset.Class;
	}
	ProjectileDeviation = 0.f;
	TimeSinceLastFire = RateOfFire;

}

// Called when the game starts or when spawned
void AWeapon_Ranged::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Display, TEXT("ProjectileSpawnLocation: %s"), *MeshComponent->GetSocketRotation(FName("BarrelSocket")).ToString());


	//MeshComponent->SetStaticMesh(Mesh);
	
	//CurrentAmmo = MagazineCapacity;
	/*
	CurrentAmmo = 0;
	RateOfFire = 0.3f;
	MagazineCapacity = 6;
	*/
	//MAXIMUM_TOTAL_AMMO = 24;
	CurrentAmmo = MagazineCapacity;
	TotalAmmo = MAXIMUM_TOTAL_AMMO;
	if (MAXIMUM_TOTAL_AMMO != 0)
	{
		TotalAmmo -= CurrentAmmo;
	}
	
}

// Called every frame
void AWeapon_Ranged::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );

	//UE_LOG(LogTemp, Display, TEXT("%d"), TimeSinceLastFire);
}

bool AWeapon_Ranged::Fire()
{
	if (Super::Fire())
	{
		//UE_LOG(LogTemp, Display, TEXT("Current ammo: %u"), CurrentAmmo);
		if (CurrentAmmo > 0)
		{
			CurrentAmmo--;
			
			if (MeshComponent->GetSocketByName(FName("BarrelSocket")))
			{
				FRotator ProjectileRotation = MeshComponent->GetSocketRotation(FName("BarrelSocket"));

				ProjectileRotation.Yaw += FMath::FRandRange(-ProjectileDeviation, ProjectileDeviation);

				AProjectile* Temp = GetWorld()->SpawnActor<AProjectile>(ProjectileToFire, MeshComponent->GetSocketLocation(FName("BarrelSocket")), ProjectileRotation);
				Temp->Damage = DamagePerAttack;
				Temp->SetOwner(OwningActor);
				//Temp->WeaponSpawnedThis = this;

				if (bOwnedByPlayer)
				{
					Temp->CollisionComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
				}
				else
				{
					Temp->CollisionComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Ignore);
				}

				if (CurrentAmmo == 0)
				{
					UE_LOG(LogTemp, Display, TEXT("Ran out of ammo after firing"));
					//Reload();
				}

				return true;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("A weapon's static mesh doesn't have a 'BarrelSocket' socket. Please add one"));
			}

			//UE_LOG(LogTemp, Display, TEXT("Rate of fire: %f"), RateOfFire);
			//UE_LOG(LogTemp, Display, TEXT("Calling Fire on a ranged weapon"));
			//UE_LOG(LogTemp, Display, TEXT("Current ammo after firing: %u"), CurrentAmmo);

		}
		if (CurrentAmmo == 0)
		{
			UE_LOG(LogTemp, Display, TEXT("Ran out of ammo after firing"));
			//Reload();
		}
		return false;
	}
	if (CurrentAmmo == 0)
	{
		//Reload();
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
	if (CurrentAmmo < MagazineCapacity)
	{
		//UE_LOG(LogTemp, Display, TEXT("Reloading")); 
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

			//UE_LOG(LogTemp, Display, TEXT("Ammo To Add: %i"), AmmoNeededToFillMagazine);
			//UE_LOG(LogTemp, Display, TEXT("Current ammo: %u"), CurrentAmmo);
			//UE_LOG(LogTemp, Display, TEXT("Total ammo: %i"), TotalAmmo);
		}
		else
		{
			//UE_LOG(LogTemp, Display, TEXT("Weapon has infinite reserve ammo"));
			CurrentAmmo = MagazineCapacity;
		}
	}
}

void AWeapon_Ranged::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);
}

bool AWeapon_Ranged::CanFire()
{
	if (CurrentAmmo > 0)
	{
		return Super::CanFire();
	}
	return false;
}

bool AWeapon_Ranged::HasAmmo()
{
	return CurrentAmmo > 0;
}

bool AWeapon_Ranged::CanReload()
{
	return CurrentAmmo < MagazineCapacity;
}
