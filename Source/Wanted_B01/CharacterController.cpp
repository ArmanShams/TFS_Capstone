// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "CharacterController.h"
#include "Wanted_B01/InteractableObject.h"


// Sets default values
ACharacterController::ACharacterController()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	moveSpeed = .4f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CUBE(TEXT("/Engine/BasicShapes/Cube.Cube"));


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CameraBoom->SetRelativeRotation(FRotator(-70.f, 0.f, 0.f));
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform);

}


// Called when the game starts or when spawned
void ACharacterController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterController::Tick( float DeltaSeconds )
{
	Super::Tick(DeltaSeconds);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	//FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	//FVector Movement = MoveDirection * moveSpeed * DeltaSeconds;

	// Two FVectors are created. mouseLocation and mouseDirection. FVector is very similar to a Vector3 from unity3d.
	// FVectors store an X, Y, and Z component.
	//FVector mouseLocation, mouseDirection;
	//APlayerController* playerController = (APlayerController*)GetWorld()->GetFirstPlayerController();

	// The mouse's location and direction are stored in FVector, since the goal is to make
	// the pawn face toward the mouse, the mouse direction is used 
	//playerController->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);

	// FRotator stores 3 values, Pitch, Yaw, and Roll.
	// FRotator requires 3 floats. Pitch and Roll are not altered.
	// Comment out this line if you prefer method 2.
	// ---Method 1---
	
}



// Called to bind functionality to input
void ACharacterController::SetupPlayerInputComponent(class UInputComponent* InInputComponent)
{
	Super::SetupPlayerInputComponent(InInputComponent);

	InInputComponent->BindAxis(TEXT("MoveForward"), this, &ThisClass::OnMoveForward);
	InInputComponent->BindAxis(TEXT("MoveRight"), this, &ThisClass::OnMoveRight);
	InInputComponent->BindAxis(TEXT("RotateMouse"), this, &ThisClass::OnMouseMove);
	InInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &ThisClass::OnInteractPressed);
	InInputComponent->BindAction(TEXT("Interact"), IE_Released, this, &ThisClass::OnInteractReleased);
	InInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &ThisClass::OnShootPressed);
	InInputComponent->BindAction(TEXT("Shoot"), IE_Released, this, &ThisClass::OnShootReleased);
	InInputComponent->BindAction(TEXT("Roll"), IE_Pressed, this, &ThisClass::OnRollPressed);

}


void ACharacterController::OnMoveForward(float scale)
{
	GetMovementComponent()->AddInputVector(GetActorForwardVector() * scale * moveSpeed);

}

void ACharacterController::OnMoveRight(float scale)
{
	GetMovementComponent()->AddInputVector(GetActorRightVector() * scale * moveSpeed);

}

void ACharacterController::OnMouseMove(float scale)
{
	// Player controller class controls pawns, not where you'd want to store controls.
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		FVector2D MousePosition;
		UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();

		if (ViewportClient && ViewportClient->GetMousePosition(MousePosition))
		{
			FVector2D CenterPoint;
			PlayerController->ProjectWorldLocationToScreen(GetMesh()->GetComponentLocation(), CenterPoint);

			FVector Diff = FVector(MousePosition.X - CenterPoint.X, MousePosition.Y - CenterPoint.Y, 0.f);

			//float yaw = Diff.Rotation().Yaw;

			GetMesh()->SetWorldRotation(FRotator(0.f, Diff.Rotation().Yaw, 0.f));

		}
	}
}

void ACharacterController::OnInteractPressed()
{

}

void ACharacterController::OnInteractReleased()
{
	//FHitResult HitResult;
	TArray<FOverlapResult> hitResult;
	GetWorld()->OverlapMultiByChannel(hitResult,
		GetActorLocation(),
		FQuat::Identity,
		ECC_Interactable,
		FCollisionShape::MakeSphere(50.0f));

	if (hitResult.Num() > 0)
	{
		if (AInteractableObject* Interactable = Cast<AInteractableObject>(hitResult[0].GetActor()))
		{
			Interactable->Interact(this);
		}
	}
}

void ACharacterController::OnRollPressed()
{

}

void ACharacterController::OnShootPressed()
{

}

void ACharacterController::OnShootReleased()
{

}
