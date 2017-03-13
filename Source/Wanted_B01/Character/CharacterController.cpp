// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "CharacterController.h"
#include "Weapons/Weapon_Ranged.h"
#include "Weapons/Weapon_PlayerRevolver.h"
#include "Environment/Interactable.h"


// Sets default values
ACharacterController::ACharacterController()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MoveSpeed = .4f;
	RollDistance = 1.f;
	Health = 100.f;
	Rage = 0.f;
	RageDrainPerSecond = 4.f;

	if (TurnRate == 0.0f)
	{
		TurnRate = 0.25f;
	}

	//UE_LOG(LogTemp, Display, TEXT("%s"), *RootComponent->GetName());

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ThisClass::OnCollision);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CameraBoom->SetRelativeRotation(FRotator(-70.f, 0.f, 0.f));
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform);


	ConstructorHelpers::FClassFinder<AWeapon>WeaponAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/PlayerRevolverBlueprint.PlayerRevolverBlueprint_C'"));
	if (WeaponAsset.Class)
	{
		UE_LOG(LogTemp, Display, TEXT("WE HAVE FOUND THE CLASS"));
		DefaultWeapon = (UClass*)WeaponAsset.Class;
	}

}


// Called when the game starts or when spawned
void ACharacterController::BeginPlay()
{
	Super::BeginPlay();
	CharacterState = State::IDLE_HUMAN;
	
	EquipRevolver();

	if (CurrentlyEquippedWeapon != NULL)
	{
		UE_LOG(LogTemp, Display, TEXT("HasGun"));
	}

	
}

// Called every frame
void ACharacterController::Tick( float DeltaSeconds )
{
	Super::Tick(DeltaSeconds);

	if (Rage >= MAXRAGE && CharacterState == State::IDLE_HUMAN)
	{
		CharacterState = State::IDLE_WOLF;
		UE_LOG(LogTemp, Display, TEXT("Player 'Transformed' to wolf"));

		USkeletalMesh* NewMesh = LoadObject<USkeletalMesh>(NULL, TEXT("SkeletalMesh'/Game/Geometry/Characters/Werewolf/M_Werewolf.M_Werewolf'"), NULL, LOAD_None, NULL);
		if (NewMesh)
		{
			GetMesh()->SetSkeletalMesh(NewMesh);
		}
	}

	if (Rage <= 0.1f && CharacterState == State::IDLE_WOLF)
	{
		CharacterState = State::IDLE_HUMAN;
		UE_LOG(LogTemp, Display, TEXT("Player 'Transformed' to human"));

		USkeletalMesh* NewMesh = LoadObject<USkeletalMesh>(NULL, TEXT("SkeletalMesh'/Game/Geometry/Characters/VincentArgo/SK_Vincent_Proxy.SK_Vincent_Proxy'"), NULL, LOAD_None, NULL);
		if (NewMesh)
		{
			GetMesh()->SetSkeletalMesh(NewMesh);
		}
	}

	if (CharacterState == State::IDLE_WOLF || CharacterState == State::ROLLING_WOLF)
	{
		Rage -= RageDrainPerSecond * DeltaSeconds;
	}
	
	switch (CharacterState)
	{
	default:
		break;

	case State::ROLLING:
		FVector CurrentPosition = (FMath::Lerp(RootComponent->RelativeLocation, RollDestination, 25.f * DeltaSeconds) - RootComponent->RelativeLocation);

		//RootComponent->SetWorldLocation(FMath::Lerp(RootComponent->RelativeLocation, RollDestination, 0.25f));
		GetMovementComponent()->AddInputVector(CurrentPosition);

		//if (RootComponent->RelativeLocation.Y >= RollDestination.Y - 5.3f && RootComponent->RelativeLocation.X >= RollDestination.X - 5.3f
		//	&& RootComponent->RelativeLocation.Y <= RollDestination.Y + 5.3f && RootComponent->RelativeLocation.X <= RollDestination.X + 5.3f)
		if (FVector::Dist(RootComponent->RelativeLocation, RollDestination) <= 5.3f)
		{
			GetMovementComponent()->StopActiveMovement();
			UE_LOG(LogTemp, Display, TEXT("Setting state to idle."));
			CharacterState = State::IDLE_HUMAN;
		}
		break;
	}
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
	InInputComponent->BindAction(TEXT("AltShoot"), IE_Pressed, this, &ThisClass::OnAltShootPressed);
	InInputComponent->BindAction(TEXT("AltShoot"), IE_Released, this, &ThisClass::OnAltShootReleased);
	InInputComponent->BindAction(TEXT("Roll"), IE_Pressed, this, &ThisClass::OnRollPressed);

	// Debug keybinding, remove later.
	InInputComponent->BindAction(TEXT("DebugRage"), IE_Pressed, this, &ThisClass::OnDebugRagePressed);

}

float ACharacterController::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float NewHealth = Health;
	NewHealth -= DamageAmount;

	if (NewHealth > MAXHEALTH)
	{
		NewHealth = MAXHEALTH;
	}

	UE_LOG(LogTemp, Display, TEXT("Player health modified, health is now: %f"), Health);

	Health = NewHealth;

	return Health;
}

void ACharacterController::ModifyHealth(float mod)
{
	// Prevention of adding health greater than the maximum currently disabled.
	
}

void ACharacterController::EquipNewWeapon(AWeapon* newWeapon)
{
	//CurrentlyEquippedWeapon = newWeapon;
}


void ACharacterController::OnMoveForward(float scale)
{
	if (CharacterState != State::ROLLING || CharacterState != State::ROLLING_WOLF)
	{
		GetMovementComponent()->AddInputVector(GetActorForwardVector() * scale * MoveSpeed);
	}
}

void ACharacterController::OnMoveRight(float scale)
{
	if (CharacterState != State::ROLLING || CharacterState != State::ROLLING_WOLF)
	{
		GetMovementComponent()->AddInputVector(GetActorRightVector() * scale * MoveSpeed);
	}
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
			
			GetMesh()->SetRelativeRotation(FMath::Lerp(GetMesh()->RelativeRotation, FRotator(0.f, Diff.Rotation().Yaw, 0.f), TurnRate));
		}
	}
}

void ACharacterController::OnInteractPressed()
{

}

void ACharacterController::OnInteractReleased()
{
	TArray<FOverlapResult> hitResult;
	GetWorld()->OverlapMultiByChannel(hitResult, GetActorLocation(), FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(50.f) );

	if (hitResult.Num() > 0) 
	{
		if (AInteractable* Interactable = Cast<AInteractable>(hitResult[0].GetActor())) 
		{
			Interactable->Interact(this);
			UE_LOG(LogTemp, Display, TEXT("Actually hit a thing."));
		}
	}
	UE_LOG(LogTemp, Display, TEXT("Interact key released"));
}

void ACharacterController::OnRollPressed()
{
	if (CharacterState == State::IDLE_HUMAN)
	{
		CharacterState = State::ROLLING;
		RollStartingPoint = RootComponent->RelativeLocation;
		FVector MovementVector = GetLastMovementInputVector();

		if (MovementVector != FVector::ZeroVector)
		{
			UE_LOG(LogTemp, Display, TEXT("Rolling!"));
			RollDestination = FVector(RollStartingPoint.X + (MovementVector.X * RollDistance), RollStartingPoint.Y + (MovementVector.Y * RollDistance), RollStartingPoint.Z);
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("Defaulting to rolling backwards"));
			//RollDestination = FVector(RollStartingPoint.X, RollStartingPoint.Y + RollDistance, RollStartingPoint.Z );
		}
	}
}

void ACharacterController::Roll()
{

}

void ACharacterController::EquipRevolver()
{
	CurrentlyEquippedWeapon = GetWorld()->SpawnActor<AWeapon>(DefaultWeapon);
	CurrentlyEquippedWeapon->SetActorRelativeRotation(FRotator(90.f, 180.f, 0.f));
	CurrentlyEquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("hand_r"));
	CurrentlyEquippedWeapon->bOwnedByPlayer = true;
}

void ACharacterController::OnShootPressed()
{
	if (CharacterState == State::IDLE_HUMAN)
	{
		CurrentlyEquippedWeapon->Fire();
	}
	
}

void ACharacterController::OnShootReleased()
{

}

void ACharacterController::OnAltShootPressed()
{
	if (CharacterState == State::IDLE_HUMAN)
	{
		CurrentlyEquippedWeapon->AltFire();
	}
}

void ACharacterController::OnAltShootReleased()
{

}

void ACharacterController::OnDebugRagePressed()
{
	if (Rage < MAXRAGE)
	{
		Rage = MAXRAGE;
		UE_LOG(LogTemp, Display, TEXT("Rage has been set to maximum %f"), Rage);
	}
	else
	{
		Rage = 0.f;
		UE_LOG(LogTemp, Display, TEXT("Rage has been set to minimum %f"), Rage);
	}
	
}

void ACharacterController::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Display, TEXT("WE ARE IN THE BEAM"));
	switch(CharacterState)
	{
	case State::ROLLING:
		//UE_LOG(LogTemp, Display, TEXT("Returning the player to the starting point of the roll, setting state to idle."));
		//CharacterState = State::IDLE_HUMAN;
		//FVector ReturnPoint = FVector(RollStartingPoint.X - Hit.Location.X, RollStartingPoint.Y - Hit.Location.Y, RollStartingPoint.Z);
		//UE_LOG(LogTemp, Display, TEXT("Roll Starting Point: %s"), *RollStartingPoint.ToString())
		RollDestination = RootComponent->RelativeLocation;
	break;
	}
}