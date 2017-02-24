// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AreaOfEffect.generated.h"

UCLASS()
class WANTED_B01_API AAreaOfEffect : public AActor
{
	GENERATED_BODY()
	
public:	

	AAreaOfEffect(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere)
	float lifeTimeInSeconds;

	UPROPERTY(EditAnywhere)
	float ticksPerSecond;
	
	UPROPERTY(EditAnywhere)
	uint8 damagePerTick;
	
	uint8 totalTicks;

	UPROPERTY(EditAnywhere)
	float radius;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	USphereComponent* sphereCollider;

private:
	UPROPERTY()
	float timeSinceLastTick;

	UPROPERTY()
	float timeOfCreation;

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
