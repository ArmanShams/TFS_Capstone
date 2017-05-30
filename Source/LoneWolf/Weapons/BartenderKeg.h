// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BartenderKeg.generated.h"

UCLASS()
class LONEWOLF_API ABartenderKeg : public AActor
{
	GENERATED_BODY()
	
public:	
	ABartenderKeg();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetOwner(AActor* NewOwner) override;

	virtual UProjectileMovementComponent* GetProjectileMovementComponent();

protected:

	class AActor* Owner;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	class UCapsuleComponent* CollisionComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	class UPrimitiveComponent* Collider;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float CapsuleRadius;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float CapsuleHalfHeight;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float InitSpeed;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float MaxSpeed;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float LifeTime;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float Damage;

	//class AWeapon_Ranged* WeaponSpawnedThis;

	// Called when projectile hits something 
	UFUNCTION()
	virtual void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	
};
