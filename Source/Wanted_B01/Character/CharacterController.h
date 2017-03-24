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

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void AddRage(float RageToAdd);
	
	void EquipNewWeapon(AWeapon* newWeapon);
	


protected:
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> wInGameHud;

	// Variable to hold the widget After Creating it.
	UUserWidget* InGameHud;


	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed;

	UPROPERTY(EditDefaultsOnly)
	float TurnRate;

	UPROPERTY(EditDefaultsOnly)
	float RollDistance;

	UPROPERTY(EditDefaultsOnly)
	float Health;

	UPROPERTY(EditDefaultsOnly)
	float Rage;

	UPROPERTY(EditDefaultsOnly)
	float RageDrainPerSecond;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	State CharacterState;

	UPROPERTY(Category = Collision, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleCollider;

	
	FVector RollStartingPoint;
	FVector RollDestination;


	TSubclassOf<AWeapon> DefaultWeapon;
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
	void OnAltShootPressed();
	void OnAltShootReleased();
	void OnDebugRagePressed();

	//UFUNCTION()
	//void OnComponentBeginOverlap(AActor* other);

	UFUNCTION()
	void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void Roll();

	void EquipRevolver();

private:
	const float MAXHEALTH = 100.f;
	const float MAXRAGE = 100.f;

	friend class UUIWidget;
};
