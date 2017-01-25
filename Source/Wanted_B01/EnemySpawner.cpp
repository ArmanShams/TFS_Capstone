// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "EnemySpawner.h"
#include "Enemy.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	enemyCount = 0;
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

	if (Iteration > 0)
	{
		TimeToSpawn -= DeltaTime;
		if (TimeToSpawn < 0.f)
			if (EnemyCount != 5)
			{
				SpawnEnemy();
				EnemyCount++;
			}
	}
}

void AEnemySpawner::SpawnEnemy()
{
	if (EnemyBP)
	{
		FActorSpawnParameters SpawnParameters;
		AEnemy *NewEnemy = GetWorld()->SpawnActor<AEnemy>(EnemyBP, GetTransform(), SpawnParameters);
		GLog->Log("Spawned an Enemy");
		GLog->Log("Spawned an Enemy");

		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemySpawner::EnemyArray, TimeToSpawn);

		NewEnemy->Iteration = Iteration - 1;
		Iteration = 0;
	}
}

void AEnemySpawner::EnemyArray()
{
	TArray<AActor*> TypeofEnemy;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), TypeofEnemy);

	AEnemy* EnemyType = Cast<AEnemy>(TypeofEnemy[0]);
	if (EnemyType)
	{
		GLog->Log("Enemy Type verrified");
	}
}