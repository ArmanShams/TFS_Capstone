// Fill out your copyright notice in the Description page of Project Settings.
// this is the enemy base class which will derive the enemys health, attacks, and status effects.

#pragma once

#include "GameFramework/Character.h"
#include "Weapons/Weapon.h"
#include "Enemy.generated.h"


UENUM(BlueprintType)
enum class EState : uint8
{
	Idle			UMETA(DisplayName = "Idle"),
	Search			UMETA(DisplayName = "Search"),
	Attack			UMETA(DisplayName = "Attack"),
	Flee			UMETA(DisplayName = "Flee")


};

UENUM(BlueprintType)
enum class Effects : uint8
{
	Stun			UMETA(DisplayName = "Stun"),
	DOT				UMETA(DisplayName = "DOT"),
	Slow			UMETA(DisplayName = "Slow"),
	Null			UMETA(DisplayName = "Null")


};

UCLASS()
class WANTED_B01_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


	void Enemy();

	UPROPERTY(EditInstanceOnly)
	TArray<class ATargetPoint*> PatrolPoints;

	bool bIsAttacking();
	
protected:
	UPROPERTY(EditAnywhere)
		float Health;

	UPROPERTY(EditAnywhere)
		float MoveSpeed;

	UPROPERTY(EditAnywhere)
		float TurnRate;

	UPROPERTY(EditDefaultsOnly)
		float MaxRange = 100.0f;

	UPROPERTY(EditAnywhere)
		float LastAttacked;

	UPROPERTY(EditAnywhere)
		float AttackFrequency;

	UPROPERTY(EditAnywhere)
		float MeleeRange = 150.0f;

	// cooldown for how frequently the skills can be used
	UPROPERTY(EditAnywhere)
		float Skill1Cooldown;

	// cooldown for how frequently the skills can be used
	UPROPERTY(EditAnywhere)
		float Skill2Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		EState EnemyState;


		TSubclassOf<AWeapon> DefaultWeapon;
		AWeapon* CurrentlyEquippedWeapon;

	UPROPERTY(EditAnywhere)
		float isInRange;

	int32 AttackType;

	void Attack(int32 AttackType);

	//enemy's basic attack which will be most frequently used can include input for status effect application
	void BasicAttack(Effects effect, float Range);

	void AttackEnd();

	//enemy's 1st skill, will include an input for status effect application
	void Skill1(Effects effect, float Range);

	//enemy's 1st skill, will include an input for status effect application
	void Skill2(Effects effect, float Range);

	void EquipKnife();

	friend class UEnemyAnimInstance;

private:
	const float MAXHEALTH = 100.f;

};
