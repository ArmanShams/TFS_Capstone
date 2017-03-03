// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "Weapons/RangedAIProjectile.h"
#include "RangedAI.h"


ARangedAI::ARangedAI()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set the root component
	RangedAIMesh = GetMesh();
	RangedAIMesh->GetComponentLocation();
	RangedAIMesh->GetComponentRotation();
	RootComponent = RangedAIMesh;

	// Attach the weapon mesh to the character mesh component
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RangedAIMesh);
	
	// Attach the spawn point for the projectile to the weapon
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(WeaponMesh);
	// ProjectileSpawnPoint->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	// ProjectileSpawnPoint->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
}

void ARangedAI::BeginPlay()
{
	Super::BeginPlay();
}

void ARangedAI::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ARangedAI::StartSimulation()
{
	OnFire();
}

void ARangedAI::EndSimulation()
{
}

void ARangedAI::OnFire()
{
	GEngine->AddOnScreenDebugMessage(-2, 1.f, FColor::White, FString::Printf(TEXT("Attack Triggered!")));
	// GetWorld()->SpawnActor<ARangedAI>();
	const FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
	const FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();

	if (ProjectileClassSpawned != NULL) {
		ARangedAIProjectile* RangedAIProjectile = GetWorld()->SpawnActor<ARangedAIProjectile>(ProjectileClassSpawned, SpawnLocation, SpawnRotation);
	}
}
