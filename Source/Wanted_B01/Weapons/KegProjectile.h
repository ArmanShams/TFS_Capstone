// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "KegProjectile.generated.h"

UCLASS()
class WANTED_B01_API AKegProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKegProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
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
	float InitSpeed = 25.0f;

	UPROPERTY(EditAnywhere, Category = Projectile)
	float MaxSpeed = 50.0f;

	UPROPERTY(EditAnywhere, Category = Projectile)
	float LifeTime = 3.0f;

	//UPROPERTY(EditAnywhere, Category = Projectile)
	//float BulletImpulse = 100.0f;

	float Damage;

	float TrailLifeTime;



	class AWeapon_Ranged* WeaponSpawnedThis;

	// Called when projectile hits something 
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	
};
