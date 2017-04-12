// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class LONEWOLF_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void SetOwner(AActor* NewOwner) override;

	//virtual  void SetOwningActor(AActor* NewOwningActor);

	virtual bool Fire();

	virtual bool AltFire();

protected:
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
