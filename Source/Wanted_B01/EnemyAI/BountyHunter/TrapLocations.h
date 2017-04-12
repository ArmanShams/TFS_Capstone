// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TrapLocations.generated.h"

UCLASS()
class WANTED_B01_API ATrapLocations : public AActor
{
	GENERATED_BODY()
	
public:	
	ATrapLocations();
	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	USphereComponent* SphereCollider;

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

	bool bIsOccupied;
	
};