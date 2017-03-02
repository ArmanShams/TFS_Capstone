// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "Weapons/RangedAIProjectile.h"
#include "RangedAI.h"


ARangedAI::ARangedAI()
{
	PrimaryActorTick.bCanEverTick = true;

	// Attach the weapon mesh to the character mesh component
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(GetMesh());

	// Attach the spawn point for the projectile to the weapon
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(WeaponMesh);
	ProjectileSpawnPoint->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	ProjectileSpawnPoint->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
}

void ARangedAI::BeginPlay()
{
	Super::BeginPlay();
}

void ARangedAI::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (bCanAttack == true)
	{
		CanAttack();
	}
}

void ARangedAI::SetupPlayerInputComponent(UInputComponent * InInputComponent)
{	
	// Run Simulation
	Super::SetupPlayerInputComponent(InInputComponent);
	InInputComponent->BindAction(TEXT("DebugTool"), IE_Pressed, this, &ThisClass::DebugTool);
}

void ARangedAI::OnFire()
{
	UWorld* const World = GetWorld();
	if (GetWorld() != nullptr)
	{
		const FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		const FRotator SpawnRotation = WeaponMesh->GetComponentRotation();
		World->SpawnActor<ARangedAIProjectile>(ProjectileClassSpawned, SpawnLocation, SpawnRotation);
	}
}

void ARangedAI::CanAttack()
{
	GEngine->AddOnScreenDebugMessage(-2, 1.f, FColor::White, FString::Printf(TEXT("Attack Triggered!")));
	if (PlayerDistance <= DetectionRange)
	{
		OnFire();
		GEngine->AddOnScreenDebugMessage(-3, 1.f, FColor::Red, FString::Printf(TEXT("Projectile Spawned!")));
	}
}

void ARangedAI::DebugTool()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, FString::Printf(TEXT("Can Attack!")));
	PlayerDistance = 5.0f;
	DetectionRange = 10.0f;
	CanAttack();
}
