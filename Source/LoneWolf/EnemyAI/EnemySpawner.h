// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Character/LoneWolfCharacter.h"
#include "EnemySpawner.generated.h"

UCLASS(Blueprintable)
class LONEWOLF_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	AEnemySpawner();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxCollider;

	UPROPERTY(EditDefaultsOnly)
	float TimeSinceLastSpawn;

	UPROPERTY(EditDefaultsOnly)
	float RateOfSpawning;

	UPROPERTY(EditDefaultsOnly, Category = Spawner)
	TSubclassOf<ALoneWolfCharacter> EnemyClass;

	FVector SpawnLocation;
	FRotator SpawnRotation;

	void SpawnEnemy();
	bool CanSpawn();

	bool bIsOverlapping;

	UFUNCTION()
	void OnPlayerOverlap(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnPlayerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};