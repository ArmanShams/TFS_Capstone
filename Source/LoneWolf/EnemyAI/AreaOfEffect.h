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

	UPROPERTY(EditDefaultsOnly, Category = "AreaOfEffect")
	float LifeTimeInSeconds;

	UPROPERTY(EditDefaultsOnly, Category = "AreaOfEffect")
	float TicksPerSecond;
	
	UPROPERTY(EditDefaultsOnly, Category = "AreaOfEffect")
	float DamagePerTick;
	
	UPROPERTY(EditDefaultsOnly, Category = "AreaOfEffect")
	float Radius;

	uint8 TotalTicks;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	USphereComponent* SphereCollider;

private:
	float TimeSinceLastTick;
	float TimeOfCreation;

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	
	
};
