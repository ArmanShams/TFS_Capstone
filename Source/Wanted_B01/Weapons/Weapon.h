// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class WANTED_B01_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(EditAnywhere)
	uint8 magCapacity;

	UPROPERTY(EditAnywhere)
	uint8 currentAmmo;

	UPROPERTY(EditAnywhere)
	uint8 totalAmmo;

	UPROPERTY(EditAnywhere)
	float rateOfFire;

	UPROPERTY(EditAnywhere)
	uint8 damagePerShot;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
};
