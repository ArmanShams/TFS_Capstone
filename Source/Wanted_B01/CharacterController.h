// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "CharacterController.generated.h"

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

	void ApplyDamage(uint8 dam);

protected:

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere)
	float moveSpeed;

	UPROPERTY(EditAnywhere)
	float rollDistance;

	UPROPERTY(EditAnywhere)
	uint8 health;



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

	void Roll();
};
