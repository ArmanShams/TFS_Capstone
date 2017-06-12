// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BearTrap.generated.h"

UCLASS()
class LONEWOLF_API ABearTrap : public AActor
{
	GENERATED_BODY()

public:
	ABearTrap();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	//Radius of the collider
	UPROPERTY(EditDefaultsOnly, Category = "BearTrap")
	float radius;
	//Damage to be applied to the applied character
	UPROPERTY(EditDefaultsOnly, Category = "BearTrap")
	float Damage;	
	//Stun time when the player overlaps a trap
	UPROPERTY(EditDefaultsOnly, Category = "BearTrap")
	float SoftStunTime;
	//Stun time when the player fails to escape from trap
	UPROPERTY(EditDefaultsOnly, Category = "BearTrap")
	float StunTime;

	virtual void SetOwner(AActor* NewOwner) override;

	virtual void Destroyed() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Collision")
	USphereComponent* TrapCollider;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh Component")
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Mesh Component")
	USkeletalMesh* Mesh;

	class ATrapLocations* LocationBeingOccupied;

	virtual void SetLocationBeingOccupied(class ATrapLocations* NewLocationBeingOccupied);

private:
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//class AActor* Bouty;

	friend class ABountyHunter;
};