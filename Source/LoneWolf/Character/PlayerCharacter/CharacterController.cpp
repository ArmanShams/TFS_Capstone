// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "CharacterController.h"
#include "Environment/Interactable.h"
#include "Weapons/Weapon.h"
#include "Weapons/Weapon_Ranged.h"
#include "Blueprint/UserWidget.h"
#include "Character/StatusEffects/StatusEffectBase.h"
#include "Character/StatusEffects/StatusEffect_HardCrowdControl.h"
#include "Character/StatusEffects/StatusEffect_TestDerivative.h"


ACharacterController::ACharacterController()
{
	PrimaryActorTick.bCanEverTick = true;

	MoveSpeed = .4f;
	RollDistance = 1.f;
	Health = 100.f;
	Rage = 0.f;
	RageDrainPerSecond = 4.f;
	bIsRolling = false;
	TurnRate = 0.25f;
	
	//Bind dynamic delegates
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ThisClass::OnCollision);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CameraBoom->SetRelativeRotation(FRotator(-70.f, 0.f, 0.f));
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform);


	ConstructorHelpers::FClassFinder<AWeapon>RangedWeaponAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/PlayerRevolverBlueprint.PlayerRevolverBlueprint_C'"));
	if (RangedWeaponAsset.Class)
	{
		//UE_LOG(LogTemp, Display, TEXT("WE HAVE FOUND THE REVOLVER CLASS"));
		DefaultWeapon = (UClass*)RangedWeaponAsset.Class;
	}
	ConstructorHelpers::FClassFinder<AWeapon>WolfMeleeWeaponAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/WolfMeleeWeapon.WolfMeleeWeapon_C'"));
	if (WolfMeleeWeaponAsset.Class)
	{
		//UE_LOG(LogTemp, Display, TEXT("WE HAVE FOUND THE WOLF MELEE CLASS"));
		WolfWeapon = (UClass*)WolfMeleeWeaponAsset.Class;
	}
	Effects = CharacterState::NONE;
	CurrentMeleeAttackType = AttackTypes::NONE;
	CurrentForm = TransformationState::HUMAN;
	bIsRolling = false;
	bIsMeleeAttacking = false;
}


void ACharacterController::BeginPlay()
{
	Super::BeginPlay();

	if (!NeuteredMode)
	{
		EquipNewWeapon(DefaultWeapon);

		if (CurrentlyEquippedWeapon != NULL)
		{
			//UE_LOG(LogTemp, Display, TEXT("HasGun"));
		}

		wInGameHud = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/Blueprints/HUD/HUD.HUD_C'"), NULL, LOAD_None, NULL);

		if (wInGameHud)
		{
			InGameHud = CreateWidget<UUserWidget>(GetWorld(), wInGameHud);

			if (!InGameHud->GetIsVisible())
			{
				//InGameHud->AddToPlayerScreen();
				InGameHud->AddToViewport(80);
			}
		}

		//AddStatusEffect(UStatusEffect_TestDerivative::StaticClass(), true, true, 5.0f, 0.0f, 1.0f, this);
	}
}

void ACharacterController::Tick( float DeltaSeconds )
{
	Super::Tick(DeltaSeconds);

	if (bIsHardCC())
	{
		UE_LOG(LogTemp, Display, TEXT("I AM IN HARD CC MY EYES HURT PLEASE SEND HELP"));
	}
	

	if (Rage >= MAXRAGE && CurrentForm == TransformationState::HUMAN)
	{
		CurrentForm = TransformationState::WOLF;
		UE_LOG(LogTemp, Display, TEXT("Player 'Transformed' to wolf"));

		//USkeletalMesh* NewMesh = LoadObject<USkeletalMesh>(NULL, TEXT("SkeletalMesh'/Game/Geometry/Characters/Werewolf/M_Werewolf.M_Werewolf'"), NULL, LOAD_None, NULL);

		USkeletalMesh* NewMesh = LoadObject<USkeletalMesh>(NULL, TEXT("SkeletalMesh'/Game/MixamoAnimPack/Mixamo_Adam/Mesh/Maximo_Adam.Maximo_Adam'"), NULL, LOAD_None, NULL);
		UAnimBlueprint* NewAnimInstance = LoadObject<UAnimBlueprint>(NULL, TEXT("AnimBlueprint'/Game/Blueprints/Player/CharacterControllerWolfPlacehonder.CharacterControllerWolfPlacehonder'"), NULL, LOAD_None, NULL);
		if (NewMesh)
		{
			GetMesh()->SetSkeletalMesh(NewMesh);
			GetMesh()->SetAnimInstanceClass(NewAnimInstance->GetAnimBlueprintGeneratedClass());

			CurrentlyEquippedWeapon = GetWorld()->SpawnActor<AWeapon>(WolfWeapon);
			//CurrentlyEquippedWeapon->SetActorRelativeRotation(FRotator(90.f, 180.f, 0.f));
			CurrentlyEquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("WeaponSocket"));
			CurrentlyEquippedWeapon->SetOwner(this);

			//CurrentlyEquippedWeapon->bOwnedByPlayer = true;
		}
	}


	if (CurrentForm == TransformationState::WOLF)
	{
		Rage -= RageDrainPerSecond * DeltaSeconds;

		if (Rage <= 0.1f)
		{
			CurrentForm = TransformationState::WOLF;
			UE_LOG(LogTemp, Display, TEXT("Player 'Transformed' to human"));

			USkeletalMesh* NewMesh = LoadObject<USkeletalMesh>(NULL, TEXT("SkeletalMesh'/Game/Geometry/Characters/VincentArgo/SK_Vincent_Proxy.SK_Vincent_Proxy'"), NULL, LOAD_None, NULL);
			if (NewMesh)
			{
				GetMesh()->SetSkeletalMesh(NewMesh);
			}
			EquipRevolver();
			Rage = 0.0f;
		}
	}

	// Tune to be dependent on Anim notifies in the future.
	if (bIsRolling)
	{
		FVector CurrentPosition = (FMath::Lerp(RootComponent->RelativeLocation, RollDestination, 25.f * DeltaSeconds) - RootComponent->RelativeLocation);

		//RootComponent->SetWorldLocation(FMath::Lerp(RootComponent->RelativeLocation, RollDestination, 0.25f));
		GetMovementComponent()->AddInputVector(CurrentPosition);

		if (bIsRolling && FVector::Dist(RootComponent->RelativeLocation, RollDestination) <= 5.3f)
		{
			GetMovementComponent()->StopActiveMovement();
			UE_LOG(LogTemp, Display, TEXT("End roll"));
			bIsRolling = false;
		}
	}

	

	switch (CurrentForm)
	{
	default:
		break;

	case TransformationState::HUMAN:
		

		break;
	}

}

void ACharacterController::SetupPlayerInputComponent(class UInputComponent* InInputComponent)
{
	Super::SetupPlayerInputComponent(InInputComponent);

	InInputComponent->BindAxis(TEXT("MoveForward"), this, &ThisClass::OnMoveForward);
	InInputComponent->BindAxis(TEXT("MoveRight"), this, &ThisClass::OnMoveRight);
	InInputComponent->BindAxis(TEXT("RotateMouse"), this, &ThisClass::OnMouseMove);

	if (!NeuteredMode)
	{
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
	

}
void ACharacterController::AddRage(float RageToAdd)
{
	float NewRage = Rage;
	NewRage += RageToAdd;

	if (NewRage > MAXRAGE)
	{
		NewRage = MAXRAGE;
	}

	Rage = NewRage;
	UE_LOG(LogTemp, Display, TEXT("Modifying rage: %f"), Rage);
}

void ACharacterController::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::AddStatusEffect(ClassToCreateFrom, bShouldPerformTickAction, LifeTime, TickRate, CharacterThatInflictedStatusEffect);
}

void ACharacterController::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, bool bShouldDealDamage, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::AddStatusEffect(ClassToCreateFrom, bShouldPerformTickAction, bShouldDealDamage, LifeTime, DamageToDeal, TickRate, CharacterThatInflictedStatusEffect);
}

float ACharacterController::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float NewHealth = Health;
	NewHealth -= DamageAmount;

	if (NewHealth > MAXHEALTH)
	{
		NewHealth = MAXHEALTH;
	}

	UE_LOG(LogTemp, Display, TEXT("Player health modified, health is now: %f"), NewHealth);

	Health = NewHealth;

	if (NewHealth <= 0.f)
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
		//SetLifeSpan(0.1f);
	}

	return Health;
}


bool ACharacterController::bIsHardCC()
{
	return Super::bIsHardCC();
}

bool ACharacterController::bIsSoftCC()
{
	return Super::bIsSoftCC();
}

void ACharacterController::EquipNewWeapon(TSubclassOf<AWeapon> WeaponToEquip)
{
	CurrentlyEquippedWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponToEquip);
	CurrentlyEquippedWeapon->SetActorRelativeRotation(FRotator(90.f, 180.f, 0.f));;
	CurrentlyEquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("hand_r"));
	CurrentlyEquippedWeapon->SetOwner(this);
}

CharacterState::StatusEffect ACharacterController::GetStatusEffect()
{
	return Effects;
}

void ACharacterController::OnMoveForward(float scale)
{
	if (!bIsRolling && !bIsSoftCC())
	{
		GetMovementComponent()->AddInputVector(GetActorForwardVector() * scale * MoveSpeed);
	}
}

void ACharacterController::OnMoveRight(float scale)
{
	if (!bIsRolling && !bIsSoftCC())
	{
		GetMovementComponent()->AddInputVector(GetActorRightVector() * scale * MoveSpeed);
	}
}

void ACharacterController::OnMouseMove(float scale)
{
	// Player controller class controls pawns, not where you'd want to store controls.
	if (!bIsHardCC())
	{
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
}

void ACharacterController::OnInteractPressed()
{

}

void ACharacterController::OnInteractReleased()
{
	if (!bIsSoftCC())
	{
		TArray<FOverlapResult> hitResult;
		GetWorld()->OverlapMultiByChannel(hitResult, GetActorLocation(), FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(50.f));

		if (hitResult.Num() > 0)
		{
			if (AInteractable* Interactable = Cast<AInteractable>(hitResult[0].GetActor()))
			{
				Interactable->Interact(this);
				UE_LOG(LogTemp, Display, TEXT("Actually hit a thing."));
			}
		}
	}
	UE_LOG(LogTemp, Display, TEXT("Interact key released"));
}

void ACharacterController::OnRollPressed()
{
	if (!bIsHardCC())
	{
		if (!bIsRolling)
		{
			FVector MovementVector = GetLastMovementInputVector();

			if (MovementVector != FVector::ZeroVector)
			{
				RollStartingPoint = RootComponent->RelativeLocation;
				UE_LOG(LogTemp, Display, TEXT("Rolling!"));
				RollDestination = FVector(RollStartingPoint.X + (MovementVector.X * RollDistance), RollStartingPoint.Y + (MovementVector.Y * RollDistance), RollStartingPoint.Z);
				bIsRolling = true;
			}
			else
			{
				//UE_LOG(LogTemp, Warning, TEXT("Defaulting to rolling backwards"));
				//RollDestination = FVector(RollStartingPoint.X, RollStartingPoint.Y + RollDistance, RollStartingPoint.Z );
			}
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
	CurrentlyEquippedWeapon->SetOwner(this);
	//CurrentlyEquippedWeapon->bOwnedByPlayer = true;
}

void ACharacterController::OnShootPressed()
{
	if (!bIsHardCC())
	{
		if (CurrentForm == TransformationState::HUMAN)
		{
			CurrentlyEquippedWeapon->Fire();
		}
		if (CurrentForm == TransformationState::WOLF)
		{
			bIsMeleeAttacking = true;
			CurrentMeleeAttackType = AttackTypes::LIGHT;
			//Cast<UCharacterWolfAnimInstance>()->bCanAttack = true;
		}
	}
}

void ACharacterController::OnShootReleased()
{

}

void ACharacterController::OnAltShootPressed()
{
	if (!bIsHardCC())
	{
		if (CurrentForm == TransformationState::HUMAN)
		{
			CurrentlyEquippedWeapon->AltFire();
		}
		if (CurrentForm == TransformationState::WOLF)
		{
			bIsMeleeAttacking = true;
			CurrentMeleeAttackType = AttackTypes::HEAVY;
			//Cast<UCharacterWolfAnimInstance>()->bCanAttack = true;
		}
	}
}

void ACharacterController::OnAltShootReleased()
{

}

void ACharacterController::OnDebugRagePressed()
{
	if (Rage <= MAXRAGE - 0.5f)
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

	if (bIsRolling)
	{
		RollDestination = RootComponent->RelativeLocation;
		bIsRolling = false;
	}
}

bool ACharacterController::IsRolling()
{
	return bIsRolling;
}

bool ACharacterController::IsMeleeAttacking()
{
	return bIsMeleeAttacking;
}

