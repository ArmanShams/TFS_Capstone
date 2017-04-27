// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "EnemySpawner.h"
#include "Character/PlayerCharacter/CharacterController.h"
#include "EnemyAI/Miner/MinerAI.h"
#include "Enemy.h"

AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	BoxCollider->SetupAttachment(RootComponent);

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnPlayerOverlap);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnPlayerOverlapEnd);

	ConstructorHelpers::FClassFinder<AMinerAI> MinerAsset(TEXT("Blueprint'/Game/Blueprints/Enemies/Miner/MinerBP.MinerBP_C'"));
	if (MinerAsset.Class)
	{
		EnemyClass = (UClass*)MinerAsset.Class;
	}
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	TimeSinceLastSpawn = 0.0f;
	RateOfSpawning = 5.0f;
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimeSinceLastSpawn += DeltaTime;

	if (GetWorld()->HasBegunPlay())
	{
		if (TimeSinceLastSpawn >= RateOfSpawning)
		{
			if (CanSpawn())
			{		
				SpawnEnemy();
				UE_LOG(LogTemp, Display, TEXT("You've hit the box, the spawner will activate"));
			}
		}
	}
}

void AEnemySpawner::SpawnEnemy()
{
	//SpawnLocation = SpawnPoint->GetComponentLocation();
	//SpawnRotation = SpawnPoint->GetComponentRotation();

	SpawnLocation = GetActorLocation();
	SpawnRotation = GetActorRotation();

	ALoneWolfCharacter* EnemyTypeSpawned = GetWorld()->SpawnActor<ALoneWolfCharacter>(EnemyClass, SpawnLocation, SpawnRotation);

	TimeSinceLastSpawn = 0.0f;
}

bool AEnemySpawner::CanSpawn()
{
	if (bIsOverlapping == true)
	{
		return true;
	}
	return false;
}

void AEnemySpawner::OnPlayerOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("Begin Overlap"));
	bIsOverlapping = true;
}

void AEnemySpawner::OnPlayerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Display, TEXT("End Overlap"));
	bIsOverlapping = false;
}
