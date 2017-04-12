// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "RangedAI.generated.h"

UCLASS()
class LONEWOLF_API ARangedAI : public ACharacter
{
	GENERATED_BODY()

public:
	ARangedAI();

	virtual void BeginPlay() override;

	virtual void Tick( float DeltaSeconds ) override;

	virtual float ARangedAI::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	bool bPlayerDistance();
	bool Aim();

protected:
	TSubclassOf<class AWeapon> DefaultWeaponClass;
	AWeapon* CurrentlyEquippedWeapon;

	UPROPERTY(EditAnywhere, Category = Weapon) 	// Placeholder audio for when the weapon is fired
	class USoundBase* FireSFX;

	float Health;
	const float MAXHEALTH = 100.f;

	UPROPERTY(EditAnywhere)
	float AttackRange = 500.0f;
	
	friend class URangedAnimInstance;

};
