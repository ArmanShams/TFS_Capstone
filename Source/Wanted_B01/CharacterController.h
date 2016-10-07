// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "CharacterController.generated.h"

UCLASS(Blueprintable)
class WANTED_B01_API ACharacterController : public APawn
{
	
	GENERATED_BODY()

private:
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMaterial* CubeMesh;

	UPROPERTY(Category = Primitive, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CubeComponent;

	float moveSpeed;

	static const FName MoveForwardBinding;

	static const FName MoveRightBinding;

public:

	// Sets default values for this pawn's properties
	ACharacterController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


	
};
