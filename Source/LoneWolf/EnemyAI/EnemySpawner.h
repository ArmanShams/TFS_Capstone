// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class LONEWOLF_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//UPROPERTY(EditAnywhere)
	//Enemy enemyToSpawn;

	UPROPERTY(EditAnywhere)
	float spawnRateInSeconds;

	UPROPERTY(EditAnywhere)
	float spawnTimer;

	uint16 enemyCount;

	void spawnEnemy();
};
