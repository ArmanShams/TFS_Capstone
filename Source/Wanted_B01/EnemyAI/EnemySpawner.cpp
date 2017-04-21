// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "EnemySpawner.h"
#include "Wanted_B01/Character/CharacterController.h"
#include "Enemy.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	spawnRateInSeconds = 15.f;

	spawnTimer = 0.f;

	enemyCount = 0;
	static ConstructorHelpers::FObjectFinder<UBlueprint> EnemyPrototype(TEXT("Blueprint'/Game/Blueprints/Enemies/BaseEnemyAI/EnemyPrototype.EnemyPrototype'"));
	//EnemyToSpawn.Add(EnemyPrototype);

	if (EnemyToSpawn.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("EnemyToSpawn has no members"));
	}

	//if (LocationToSpawn.Num() == 0)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("LocationToSpawn has no members"));
	//}
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	spawnTimer++;

	if (spawnTimer == spawnRateInSeconds && enemyCount != 5)
	{
		spawnEnemy();
	}
}

void AEnemySpawner::spawnEnemy()
{
	//spawn enemy

	//FVector Player = Cast<ACharacterController>(GetActorLocation());


	//FVector Location (0.0f, 0.0f, 0.0f);
	//FRotator Rotation (0.0f, 0.0f, 0.0f);
	//FActorSpawnParameters SpawnInfo;
	//GetWorld()->SpawnActor<AProjectile>(Location, Rotation, SpawnInfo);

}