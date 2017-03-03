// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "RangedAI.generated.h"

UCLASS()
class WANTED_B01_API ARangedAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARangedAI();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Creates the array of projectile classes spawned
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ARangedAIProjectile> ProjectileClassSpawned;

	// Location on gun mesh where projectiles should spawn.
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class USceneComponent* ProjectileSpawnPoint;

	// Enemy Weapon Mesh
	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
	class UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* RangedAIMesh;

	// Placeholder audio for when the weapon is fired
	// UPROPERTY(EditAnywhere, Category = Weapon)
	// class USoundBase* FireSFX;

	// Weapon's offset location from the character's location
	// UPROPERTY(EditAnywhere, Category = Weapon)
	// FVector WeaponOffset;

	void StartSimulation();
	void EndSimulation();

protected:
	void OnFire();

};
