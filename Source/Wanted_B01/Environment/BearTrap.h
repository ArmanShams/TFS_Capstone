// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BearTrap.generated.h"

UCLASS()
class WANTED_B01_API ABearTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	ABearTrap();
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
	float radius;
	float Damage;

	UPROPERTY(EditAnywhere)
	bool bIsVisible;

	virtual void SetOwner(AActor* NewOwner) override;

	virtual void Destroyed() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Collision")
		USphereComponent* TrapCollider;

	class ATrapLocations* LocationBeingOccupied;

	virtual void SetLocationBeingOccupied(class ATrapLocations* NewLocationBeingOccupied);

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	class ABountyHunter* BountyHunter;

	friend class ABountyHunter;
};