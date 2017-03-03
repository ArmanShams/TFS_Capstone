// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Weapons/Weapon.h"
#include "Weapon_Ranged.generated.h"

UCLASS()
class WANTED_B01_API AWeapon_Ranged : public AWeapon
{
	GENERATED_BODY()


public:	

	// Sets default values for this actor's properties
	AWeapon_Ranged();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	virtual bool Fire() override;

	virtual void Reload();

protected:
	UPROPERTY(EditDefaultsOnly)
	uint8 MagazineCapacity;

	UPROPERTY(EditDefaultsOnly)
	uint8 MAXIMUM_TOTAL_AMMO;

	UPROPERTY(EditDefaultsOnly)
	uint8 CurrentAmmo;

	UPROPERTY(EditDefaultsOnly)
	int8 TotalAmmo;

	
};
