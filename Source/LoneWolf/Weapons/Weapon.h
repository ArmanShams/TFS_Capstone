// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class LONEWOLF_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetOwner(AActor* NewOwner) override;
	virtual bool Fire();
	virtual bool AltFire();
	virtual bool CanFire();

protected:
	UPROPERTY(EditInstanceOnly)
	bool bOwnedByPlayer;

	UPROPERTY(EditDefaultsOnly)
	float RateOfFire;

	float TimeSinceLastFire;

	UPROPERTY(EditDefaultsOnly)
	float DamagePerAttack;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class UStaticMeshComponent* MeshComponent;



	class AActor* OwningActor;
};
