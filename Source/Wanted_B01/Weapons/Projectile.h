// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class WANTED_B01_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

	virtual void BeginPlay() override;

	virtual void Tick( float DeltaSeconds ) override;

protected:

	// Sphere collision component
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class UStaticMeshComponent* MeshComponent;

	// Projectile movement component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovementComponent;
	
	UPROPERTY(EditAnywhere, Category = Collision)
	float SphereRadius = 5.0f;

	UPROPERTY(EditAnywhere, Category = Projectile)
	float InitSpeed = 100.0f;

	UPROPERTY(EditAnywhere, Category = Projectile)
	float MaxSpeed = 100.0f;

	UPROPERTY(EditAnywhere, Category = Projectile)
	float LifeTime = 3.0f;

	UPROPERTY(EditAnywhere, Category = Projectile)
	float BulletImpulse = 100.0f;

	float Damage;

	class AWeapon_Ranged* WeaponSpawnedThis;

	// Called when projectile hits something 
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	friend class AWeapon_Ranged;
	friend class AWeapon_PlayerRevolver;
};
