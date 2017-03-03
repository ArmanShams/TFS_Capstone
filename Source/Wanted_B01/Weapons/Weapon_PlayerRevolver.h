// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapons/Weapon_Ranged.h"
#include "Weapon_PlayerRevolver.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_B01_API AWeapon_PlayerRevolver : public AWeapon_Ranged
{
	GENERATED_BODY()


public:
	AWeapon_PlayerRevolver();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual bool Fire() override;

	virtual void Reload() override;
	
	
};
