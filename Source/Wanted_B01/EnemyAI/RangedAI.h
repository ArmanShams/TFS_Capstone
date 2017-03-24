// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
// #include "Weapon/Ranged_Weapon.h"
#include "RangedAI.generated.h"

UCLASS()
class WANTED_B01_API ARangedAI : public ACharacter
{
	GENERATED_BODY()

public:
	ARangedAI();

	virtual void BeginPlay() override;

	virtual void Tick( float DeltaSeconds ) override;

	virtual float ARangedAI::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Enemy Weapon Mesh
	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
	class UStaticMeshComponent* WeaponMesh;

	// Placeholder audio for when the weapon is fired
	UPROPERTY(EditAnywhere, Category = Weapon)
	class USoundBase* FireSFX;

	// Wseapon's offset location from the character's location
	//UPROPERTY(EditAnywhere, Category = Weapon)
	//FVector WeaponOffset;
	float Health;
	const float MAXHEALTH = 100.f;

	// Get the temporary gun class
	//UPROPERTY(EditDefaultsOnly, Category = Weapon)
	TSubclassOf<class AWeapon> DefaultWeaponClass;
	AWeapon* CurrentlyEquippedWeapon;


};
