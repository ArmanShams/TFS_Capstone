// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class WANTED_B01_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
	FVector initialVelocity;

	UPROPERTY(EditAnywhere)
	float travelSpeed;
	
	UPROPERTY(EditAnywhere)
	uint8 damageOnImpact;

	UPROPERTY(EditAnywhere)
	float lifetimeInSeconds;

	void OnCollision();
};
