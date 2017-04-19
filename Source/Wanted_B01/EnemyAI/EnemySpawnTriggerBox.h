// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class WANTED_B01_API EnemySpawnTriggerBox
{

public:
	EnemySpawnTriggerBox();
	~EnemySpawnTriggerBox();

	bool triggered;

	/*List of enemies to spawn at or near spawn location*/
	UPROPERTY(EditAnywhere, Catagory = "Spawner")
	TArray<TSubclassOf<class AEnemy>> EnemyToSpawn;

	/* Spawn location. If not set, no enemies spawn. */
	UPROPERTY(EditAnywhere, Catagory = "Spawner")
	class ATargetPoint* SpawnLocation;

	/* Number of copies of each type of enemy to spawn */
	UPROPERTY(EditAnywhere, Catagory = "Spawner")
	int32 Count;

	/* This value indicates the maximum number of times the spawner will trigger, if 0 the default of 1 is assumed. */
	UPROPERTY(EditAnywhere, Catagory = "Spawner")
	int32 MaxTriggers;

	UFUNCTION()
	void OnBeginOverlap(AActor* Other, UPrimitiveComponent* Box, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &hitResult);

	UFUNCTION()
	void OnEndOverlap(class AActor * OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
