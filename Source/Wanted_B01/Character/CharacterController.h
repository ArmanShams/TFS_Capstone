// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Weapons/Weapon.h"
#include "CharacterController.generated.h"

UENUM(BlueprintType)
enum class State : uint8
{
	IDLE_HUMAN		UMETA(DisplayName = "Idle"),
	IDLE_WOLF		UMETA(DisplayName = "Idle_Wolf"),
	ROLLING			UMETA(DisplayName = "Rolling"),
	ROLLING_WOLF	UMETA(DisplayName = "Rolling_Wolf")

};

UCLASS(Blueprintable)
class WANTED_B01_API ACharacterController : public ACharacter
{
	
	GENERATED_BODY()

public:

	// Sets default values for this pawn's properties
	ACharacterController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InInputComponent) override;

	void ModifyHealth(uint8 mod);

	void EquipNewWeapon(AWeapon* newWeapon);

protected:

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere)
	float MoveSpeed;

	UPROPERTY(EditAnywhere)
	float TurnRate;

	UPROPERTY(EditAnywhere)
	float RollDistance;

	UPROPERTY(EditAnywhere)
	uint8 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	State CharacterState;

	UPROPERTY(Category = Collision, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleCollider;

	

	FVector RollStartingPoint;
	FVector RollDestination;


	AWeapon* CurrentlyEquippedWeapon;


protected:
	void OnMoveForward(float scale);
	void OnMoveRight(float scale);
	void OnMouseMove(float scale);
	void OnInteractPressed();
	void OnInteractReleased();
	void OnRollPressed();
	//void OnRollReleased();
	void OnShootPressed();
	void OnShootReleased();

	//UFUNCTION()
	//void OnComponentBeginOverlap(AActor* other);

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	void Roll();
};
