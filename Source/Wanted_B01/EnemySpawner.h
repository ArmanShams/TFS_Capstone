// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class WANTED_B01_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	uint16 EnemyCount;
	uint16 Iteration;
	
	UPROPERTY(EditAnywhere, Category = "Enemy Spawning")
		TSubclassOf<AEnemy> EnemyBP;

	UPROPERTY(EditDefaultsOnly, Category = "Enemy Spawning")
		float TimeToSpawn;

	UFUNCTION()
		void SpawnEnemy();

	UFUNCTION()
		void EnemyArray();
};
