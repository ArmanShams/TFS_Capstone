// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "CharacterController.h"

const FName ACharacterController::MoveForwardBinding("MoveForward");
const FName ACharacterController::MoveRightBinding("MoveRight");

// Sets default values
ACharacterController::ACharacterController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	moveSpeed = 1000.0f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CUBE(TEXT("/Engine/BasicShapes/Cube.Cube"));

	CubeComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("THE CUBE!"));
	CubeComponent->AttachTo(RootComponent);
	RootComponent = CubeComponent;

	CubeComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

}

// Called when the game starts or when spawned
void ACharacterController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterController::Tick( float DeltaSeconds )
{
	//Super::Tick(DeltaSeconds);

	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * moveSpeed * DeltaSeconds;

	// Two FVectors are created. mouseLocation and mouseDirection. FVector is very similar to a Vector3 from unity3d.
	// FVectors store an X, Y, and Z component.
	FVector mouseLocation, mouseDirection;
	APlayerController* playerController = (APlayerController*)GetWorld()->GetFirstPlayerController();

	// The mouse's location and direction are stored in FVector, since the goal is to make
	// the pawn face toward the mouse, the mouse direction is used 
	playerController->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);

	// FRotator stores 3 values, Pitch, Yaw, and Roll.
	// FRotator requires 3 floats. Pitch and Roll are not altered.
	// Comment out this line if you prefer method 2.
	// ---Method 1---
	FRotator temp = FRotator(0.0f, mouseDirection.Rotation().Yaw, 0.0f);

	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);

		//RootComponent->MoveComponent(Movement, NewRotation, true, &Hit );

		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			//RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}

	if (temp.Yaw != 0.0f)
		RootComponent->MoveComponent(Movement, temp, true);
	else
	{
		RootComponent->MoveComponent(Movement, Movement.Rotation(), true);
	}
	
	UE_LOG(PlayerControl, Warning, Movement.);
}

// Called to bind functionality to input
void ACharacterController::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	InputComponent->BindAxis(MoveRightBinding);
	InputComponent->BindAxis(MoveForwardBinding);

	//Super::SetupPlayerInputComponent(InputComponent);
}

