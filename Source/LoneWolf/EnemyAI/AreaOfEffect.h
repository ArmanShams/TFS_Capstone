// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AreaOfEffect.generated.h"

UCLASS()
class LONEWOLF_API AAreaOfEffect : public AActor
{
	GENERATED_BODY()
	
public:	

	AAreaOfEffect(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditDefaultsOnly)
	float lifeTimeInSeconds;

	UPROPERTY(EditDefaultsOnly)
	float ticksPerSecond;
	
	UPROPERTY(EditDefaultsOnly)
	float damagePerTick;
	
	UPROPERTY(EditDefaultsOnly)
	float radius;

	uint8 totalTicks;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	USphereComponent* sphereCollider;

private:
	float timeSinceLastTick;
	float timeOfCreation;

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	
	
};
