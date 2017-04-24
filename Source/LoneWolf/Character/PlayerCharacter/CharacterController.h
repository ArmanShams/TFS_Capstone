// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Character/LoneWolfCharacter.h"
#include "CharacterController.generated.h"


UENUM(BlueprintType)
enum class TransformationState : uint8
{
	HUMAN		UMETA(DisplayName = "Human"),
	WOLF		UMETA(DisplayName = "Wolf")
};

UCLASS(Blueprintable)
class LONEWOLF_API ACharacterController : public ALoneWolfCharacter
{
	
	GENERATED_BODY()

public:
	ACharacterController();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InInputComponent) override;
	virtual void AddRage(float RageToAdd);
	virtual void AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect) override;
	virtual void AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, bool bShouldDealDamage, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect) override;
	virtual AWeapon* EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual bool bIsHardCC() override;
	virtual bool bIsSoftCC() override;

	virtual CharacterState::StatusEffect GetStatusEffect();
	
	//virtual bool bIsAttacking();

	void OnMoveForward(float scale);
	void OnMoveRight(float scale);
	void OnMouseMove(float scale);
	void OnInteractPressed();
	void OnInteractReleased();
	void OnRollPressed();
	//void OnRollReleased();
	void OnShootPressed();
	void OnShootReleased();
	void OnAltShootPressed();
	void OnAltShootReleased();
	void OnDebugRagePressed();
	void Roll();
	void OnReloadPressed();

	// SOON TO BE REMOVED
	void EquipRevolver();

	//UFUNCTION()
	//void OnComponentBeginOverlap(AActor* other);

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void OnAimSnapBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnAimSnapOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	bool IsRolling();
	bool IsMeleeAttacking();

	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed;

	UPROPERTY(EditDefaultsOnly)
	float TurnRate;

	UPROPERTY(EditDefaultsOnly)
	float Health;

	// SOON TO BE REMOVED WHEN ROLL ANIMATION IS IMPLEMENTED
	UPROPERTY(EditDefaultsOnly)
	float RollDistance;

	//UPROPERTY(EditDefaultsOnly)
	float Rage;

	UPROPERTY(EditDefaultsOnly)
	float CameraArmDistance;

	UPROPERTY(EditDefaultsOnly)
	float RageDrainPerSecond;
	
	UPROPERTY(EditDefaultsOnly)
	float AimSnapHalfHeight;
	UPROPERTY(EditDefaultsOnly)
	float AimSnapRadius;
	//UPROPERTY(EditDefaultsOnly)
	//	float Health;

	bool bIsMeleeAttacking;
	bool bIsRolling;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(Category = Collision, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleCollider;

	UPROPERTY(Category = Collision, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* AimSnapCapsule;

	TSubclassOf<class AWeapon> DefaultWeapon;
	TSubclassOf<class AWeapon> WolfWeapon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> wInGameHud;

	// Variable to store the widget after creating it.
	class UUserWidget* InGameHud;


	TransformationState CurrentForm;
	AttackTypes::MeleeAttackType CurrentMeleeAttackType;
	CharacterState::StatusEffect Effects;

	// Remove when Roll animation is added, tie to anim notifies to start and end the roll	
	FVector RollStartingPoint;
	FVector RollDestination;

	

private:
	bool NeuteredMode = false;

	const float MAXHEALTH = 100.f;
	const float MAXRAGE = 100.f;

	friend class UCharacterWolfAnimInstance;
	friend class UUIWidget;
};
