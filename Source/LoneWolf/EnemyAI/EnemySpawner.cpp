// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "EnemySpawner.h"
#include "Enemy.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	spawnRateInSeconds = 15.f;

	spawnTimer = 0.f;

	enemyCount = 0;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	spawnTimer++;

	if (spawnTimer == spawnRateInSeconds && enemyCount != 5)
	{
		spawnEnemy();
	}
}

void AEnemySpawner::spawnEnemy()
{
	//spawn enemy
}