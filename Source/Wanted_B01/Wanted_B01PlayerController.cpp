// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Wanted_B01.h"
#include "Wanted_B01PlayerController.h"
#include "AI/Navigation/NavigationSystem.h"

AWanted_B01PlayerController::AWanted_B01PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AWanted_B01PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

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

	//PlayerPawnBPClass->MoveComponent(new FVector(0, 0, 0), temp, true);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void AWanted_B01PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AWanted_B01PlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AWanted_B01PlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AWanted_B01PlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AWanted_B01PlayerController::MoveToTouchLocation);
}

void AWanted_B01PlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void AWanted_B01PlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AWanted_B01PlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AWanted_B01PlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AWanted_B01PlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
