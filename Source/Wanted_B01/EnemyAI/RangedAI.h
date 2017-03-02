// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "RangedAI.generated.h"

UENUM(BlueprintType)
enum class RangedEnemyState : uint8
{
	Idle			UMETA(DisplayName = "Idle"), //	UMETA as it appears in the editor
	Targeting		UMETA(DisplayName = "Target"),
	Attacking		UMETA(DisplayName = "Attack"),
	Fleeing			UMETA(DisplayName = "Flee"),

};


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

	// Projectile class to spawn
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ARangedAIProjectile> ProjectileClassSpawned;

	// Playtesting whether or not the enemy can shoot
	virtual void SetupPlayerInputComponent(class UInputComponent* InInputComponent) override;

	// Location on gun mesh where projectiles should spawn.
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* ProjectileSpawnPoint;

	// Enemy Weapon Mesh
	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
	class UStaticMeshComponent* WeaponMesh;

	// Placeholder audio for when the weapon is fired
	UPROPERTY(EditAnywhere, Category = Weapon)
	class USoundBase* FireSFX;

	// Weapon's offset location from the character's location
	UPROPERTY(EditAnywhere, Category = Weapon)
	FVector WeaponOffset;

	bool bCanAttack;

protected:
	void OnFire();
	void CanAttack();
	void DebugTool();

	uint8 Health;
	uint8 Ammo;
	
	float MoveSpeed;
	float TurnRate;
	
	float PlayerDistance;
	float DetectionRange;
};
