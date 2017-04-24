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
	ConstructorHelpers::FClassFinder<AEnemy> EnemyPrototype(TEXT("Blueprint'/Game/Blueprints/Enemies/BaseEnemyAI/EnemyPrototype.EnemyPrototype_C'"));
	//EnemyToSpawn.Add(EnemyPrototype);

	if (EnemyPrototype.Class)
	{
		//UE_LOG(LogTemp, Warning, TEXT("EnemyToSpawn has no members"));
		UE_LOG(LogTemp, Warning, TEXT("EnemyPrototype Class has been found"));
	}

	FVector SpawnGate = GetActorLocation();
	//ConstructorHelpers::FObjectFinder<AActor> SpawnGate(TEXT("Blueprint'/Game/Blueprints/Enemies/BaseEnemyAI/EnemySpawnGate.EnemySpawnGate_C'"));
	//FVector here = SpawnGate.Object->GetActorLocation();
	//if (SpawnGate.Object)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("SpawnGate Object has been found"));
	//}
	
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

	//AEnemy* TestSpawn;
	//FVector SpawnHere = GetActorLocation();
	//FRotator Rotation (0.0f, 0.0f, 0.0f);
	//FActorSpawnParameters SpawnInfo;
	//GetWorld()->SpawnActor(AEnemy* EnemyPrototype, Rotation, SpawnInfo )
	//	SpawnActor<EnemyPrototype>(SpawnHere, Rotation, SpawnInfo);
	//enemyCount++;
	
	UE_LOG(LogTemp, Warning, TEXT("I should have spawned"));
}