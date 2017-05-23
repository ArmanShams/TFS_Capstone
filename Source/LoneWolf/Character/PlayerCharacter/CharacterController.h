// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Character/LoneWolfCharacter.h"
#include "CharacterController.generated.h"


UENUM(BlueprintType)
enum class TransformationState : uint8
{
	DEAD		UMETA(DisplayName = "Dead"),
	HUMAN		UMETA(DisplayName = "Human"),
	WOLF		UMETA(DisplayName = "Wolf")
};

UENUM(BlueprintType)
enum class EightDirectional : uint8
{
	NONE			UMETA(DisplayName = "NONE"),
	RIGHT			UMETA(DisplayName = "Right"),
	DOWN_RIGHT		UMETA(DisplayName = "Down Right"),
	DOWN			UMETA(DisplayName = "Down"),
	DOWN_LEFT		UMETA(DisplayName = "Down Left"),
	LEFT			UMETA(DisplayName = "Left"),
	UP_LEFT			UMETA(DisplayName = "Up Left"),
	UP				UMETA(DisplayName = "Up"),
	UP_RIGHT		UMETA(DisplayName = "Up Right"),
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
	virtual bool GetbIsInHardCC() override;
	virtual bool GetbIsInSoftCC() override;
	virtual AWeapon* EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
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

	EightDirectional GetRelativeFacing();
	EightDirectional GetRelativeMovement();


	// SOON TO BE REMOVED
	//void EquipRevolver();


	//UFUNCTION()
	//void OnComponentBeginOverlap(AActor* other);

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void OnAimSnapBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnAimSnapOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	virtual bool bIsHardCC() override;
	virtual bool bIsSoftCC() override;

	bool IsRolling();
	bool IsMeleeAttacking();
	bool bEnterReloadAnimation();
	void Reload();
	virtual void Die() override;
	virtual void TransformIntoWolf();
	virtual void TransformIntoHuman();
	virtual void DespawnCurrentWeapon();
	virtual void RevokeControlAndBecomeInvulnerable();
	virtual void RestoreControlAndRevokeInvulnerable();
	virtual void OrientMeshToMovementDirection();
	EightDirectional RelativeFacingDirection(float Rotation);
	EightDirectional RelativeMovementDirection();

	bool bShouldEnterReload;
	bool bShouldEnterRoll;
	bool bAnimPrimaryFire;
	bool bAnimSecondaryFire;
	bool bIsMeleeAttacking;
	bool bIsRolling;
	bool bRecenterMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float CameraArmDistance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	float TurnRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	float Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	float RollSpeed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	float RageDrainPerSecond;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	float AimSnapHalfHeight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	float AimSnapRadius;
	float Rage;
	float DiffYaw;
	float AimOffsetYaw;
	float AnimMovementSpeed;
	float AnimMovementDirection;

	int8 HorizontalMove;
	int8 VerticalMove;

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
	

	// HUD Widget references
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> wInGameHud;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> wDeadHud;


	// Variable to store the widget after creating it.
	class UUserWidget* InGameHud;
	class UUserWidget* DeadHud;


	// Animation classes
	class UClass* WolfAnimationClass;
	class UClass* HumanAnimationClass;

	// Mesh assets
	USkeletalMesh* WolfMesh;
	USkeletalMesh* HumanMesh;


	UPROPERTY(BlueprintReadOnly, Category = "PlayerTransformationState")
	TransformationState CurrentForm;
	UAttackTypes::MeleeAttackType CurrentMeleeAttackType;
	CharacterState::StatusEffect Effects;
	EightDirectional LookDirection;
	EightDirectional MoveDirection;

	FVector RollDirection;

private:
	bool NeuteredMode = false;

	float RollCompensationYaw;
	const float MAXHEALTH = 100.f;
	const float MAXRAGE = 100.f;

	friend class UCharacterHumanAnimInstance;
	friend class UCharacterWolfAnimInstance;
	friend class UUIWidget;
};
