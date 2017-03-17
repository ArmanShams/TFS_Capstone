// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapons/Weapon.h"
#include "Weapon_Melee.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_B01_API AWeapon_Melee : public AWeapon
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AWeapon_Melee();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual bool Fire() override;

	virtual bool AltFire() override;


protected:
	UFUNCTION()
	void OnMeleeWeaponOverlapBegin(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class UCapsuleComponent* CapsuleComponent;
	
};
