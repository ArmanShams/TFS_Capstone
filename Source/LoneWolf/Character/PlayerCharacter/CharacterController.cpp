// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "CharacterController.h"
#include "Environment/Interactable.h"
#include "CharacterHumanAnimInstance.h"
#include "CharacterWolfAnimInstance.h"
#include "Weapons/Weapon.h"
#include "Weapons/Weapon_Ranged.h"
#include "Weapons/Weapon_PlayerRevolver.h"
#include "Blueprint/UserWidget.h"
#include "Character/StatusEffects/StatusEffects.h"
#include "Viewport/LoneWolfViewportClient.h"
#include "AimSnapSurface.h"

ACharacterController::ACharacterController()
{
	PrimaryActorTick.bCanEverTick = true;

	MoveSpeedBase = .4f;
	MoveSpeedActual = MoveSpeedBase;
	AnimMovementSpeed = 0.f;
	AnimMovementDirection = 0.f;
	RollSpeed = 400.f;
	Health = 100.f;
	Rage = 0.f;
	AimOffsetYaw = 0.f;
	WolfDamageTakenMultiplier = 0.65f;
	RageDrainPerSecond = 4.f;
	TurnRate = 0.25f;
	bIsRolling = false;
	bIsMeleeAttacking = false;
	bShouldEnterReload = false;
	bAnimPrimaryFire = false;
	bAnimSecondaryFire = false;
	bIsInHardCC = false;
	bIsInSoftCC = false;
	bRecenterMesh = false;


	AimSnapHalfHeight = 256.f;
	AimSnapRadius = 128.;

	CameraArmDistance = 600.f;

	AimSnapCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("AimSnapCapsule"));
	//AimSnapCapsule->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	AimSnapCapsule->SetupAttachment(RootComponent);
	AimSnapCapsule->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ECanBeCharacterBase StepUpResponse = ECanBeCharacterBase::ECB_No;
	TEnumAsByte<ECanBeCharacterBase> StepUpResponseByte = StepUpResponse;
	AimSnapCapsule->CanCharacterStepUpOn = StepUpResponseByte;
	AimSnapCapsule->SetCanEverAffectNavigation(false);
	AimSnapCapsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	AimSnapCapsule->SetCapsuleHalfHeight(AimSnapHalfHeight);
	AimSnapCapsule->SetCapsuleRadius(AimSnapRadius);

	//Bind dynamic delegates
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ThisClass::OnCollision);
	AimSnapCapsule->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnAimSnapBeginOverlap);
	AimSnapCapsule->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnAimSnapOverlapEnd);


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CameraBoom->SetRelativeRotation(FRotator(-70.f, 0.f, 0.f));
	CameraBoom->TargetArmLength = CameraArmDistance;
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
	CurrentMeleeAttackType = UAttackTypes::NONE;
	CurrentForm = TransformationState::HUMAN;
}

void ACharacterController::BeginPlay()
{
	CurrentForm = TransformationState::HUMAN;
	AimSnapCapsule->SetCapsuleHalfHeight(AimSnapHalfHeight);
	AimSnapCapsule->SetCapsuleRadius(AimSnapRadius);
	AimSnapCapsule->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	MoveSpeedActual = MoveSpeedBase;

	WolfMesh = LoadObject<USkeletalMesh>(NULL, TEXT("SkeletalMesh'/Game/Geometry/Characters/Werewolf/SK_Werewolf.SK_Werewolf'"), NULL, LOAD_None, NULL);
	FString AnimClassStringWolf = "AnimBlueprint'/Game/Animation/Wolf/CharacterControllerWolf_AnimBP.CharacterControllerWolf_AnimBP_C'";
	WolfAnimationClass = LoadObject<UClass>(NULL, *AnimClassStringWolf);

	HumanMesh = GetMesh()->SkeletalMesh;
	FString AnimClassStringHuman = "Class'/Game/Animation/Vincent/Character_Controller_AnimBP.Character_Controller_AnimBP_C'";
	HumanAnimationClass = LoadObject<UClass>(NULL, *AnimClassStringHuman);
	GetMesh()->SetAnimInstanceClass(HumanAnimationClass);

	
	Super::BeginPlay();

	if (ULoneWolfViewportClient* RecastViewport = Cast<ULoneWolfViewportClient>(GetWorld()->GetGameViewport()))
	{
		if (!RecastViewport->OnFocusLost.IsBound())
		{
			RecastViewport->OnFocusLost.AddDynamic(this, &ThisClass::OnGameFocusLost);

			auto CurrentFocus = FSlateApplication::Get().GetKeyboardFocusedWidget();
			FSlateApplication::Get().ClearKeyboardFocus(EKeyboardFocusCause::SetDirectly);
			FSlateApplication::Get().SetKeyboardFocus(CurrentFocus);
		}
	}

	if (!NeuteredMode)
	{
		EquipNewWeapon(DefaultWeapon);

		if (CurrentlyEquippedWeapon != NULL)
		{
			//UE_LOG(LogTemp, Display, TEXT("HasGun"));
		}

		wInGameHud = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/Blueprints/HUD/HUD.HUD_C'"), NULL, LOAD_None, NULL);
		wDeadHud = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/Blueprints/HUD/DeadHud.DeadHud_C'"), NULL, LOAD_None, NULL);

		if (wInGameHud)
		{
			InGameHud = CreateWidget<UUserWidget>(GetWorld(), wInGameHud);
			if (!InGameHud->GetIsVisible())
			{
				InGameHud->AddToViewport(80);
				if (APlayerController* RecastController = Cast<APlayerController>(GetController()))
				{
					//InGameHud->SetUserFocus(RecastController);
					FInputModeGameAndUI Mode;
					FInputModeGameOnly NewMode;
					Mode.SetHideCursorDuringCapture(false);
					//Mode.SetWidgetToFocus(InGameHud->GetCachedWidget());
					RecastController->SetInputMode(NewMode);
					RecastController->bShowMouseCursor = false;
					RecastController->CurrentMouseCursor = EMouseCursor::None;
				}
			}
		}
		
		//Regardless of actor spawn rotation, the roll will compensate to always align with movement vector.
		float DefaultYaw = GetActorRotation().Yaw;
		if (DefaultYaw < -0.1f)
		{
			RollCompensationYaw = -DefaultYaw - 90.f;
		}
		else if (DefaultYaw > 0.1f)
		{
			RollCompensationYaw = -90.f - DefaultYaw;
		}
		else
		{
			RollCompensationYaw = -90.f;
		}
		
	}
}

void ACharacterController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector LastInputVector = GetMovementComponent()->GetLastInputVector();
	if (bIsRolling && RollDirection != FVector::ZeroVector)
	{
		if (CurrentForm == TransformationState::WOLF)
		{
			GetMovementComponent()->AddInputVector(RollDirection * (RollSpeed * 1.5f));
		}
		else
		{
			GetMovementComponent()->AddInputVector(RollDirection * RollSpeed);
		}
	}

	float LookYaw = DiffYaw;
	if (LookYaw < 0.f)
	{
		LookYaw += 360.f;
	}
	//UE_LOG(LogTemp, Display, TEXT("Mesh rotation yaw = %f"), LookYaw);

	LookDirection = RelativeFacingDirection(LookYaw);
	MoveDirection = RelativeMovementDirection();

	// Debug statements for eight axis movement and rotation.

	switch (CurrentForm)
	{
	case TransformationState::DEAD:
		break;
	case TransformationState::HUMAN:
		if (AWeapon_Ranged* RecastRangedWeapon = Cast<AWeapon_Ranged>(CurrentlyEquippedWeapon))
		{
			if (!RecastRangedWeapon->HasAmmo())
			{
				bShouldEnterReload = true;
			}
			if (AWeapon_PlayerRevolver* RecastWeaponToRevolver = Cast<AWeapon_PlayerRevolver>(RecastRangedWeapon))
			{
				bAnimSecondaryFire = RecastWeaponToRevolver->IsFanFiring();
			}
		}
		break;
	case TransformationState::WOLF:
		Rage -= RageDrainPerSecond * DeltaSeconds;

		if (Rage <= 0.1f)
		{

			

			CurrentForm = TransformationState::HUMAN;


		}
		break;
	default:
		break;
	}
	//bIsInHardCC = bIsHardCC();
	//bIsInSoftCC = bIsSoftCC();
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
		InInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &ThisClass::OnReloadPressed);

		// Debug key binding, remove later.
		InInputComponent->BindAction(TEXT("DEBUG_RAGE"), IE_Pressed, this, &ThisClass::OnDebugRagePressed);
		InInputComponent->BindAction(TEXT("Transform"), IE_Pressed, this, &ThisClass::OnTransformPressed);
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
	if (!bIsRolling)
	{
		Super::AddStatusEffect(ClassToCreateFrom, bShouldPerformTickAction, LifeTime, TickRate, CharacterThatInflictedStatusEffect);
	}
}

void ACharacterController::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, bool bShouldDealDamage, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	if (!bIsRolling)
	{
		Super::AddStatusEffect(ClassToCreateFrom, bShouldPerformTickAction, bShouldDealDamage, LifeTime, DamageToDeal, TickRate, CharacterThatInflictedStatusEffect);
	}
}

bool ACharacterController::GetbIsInHardCC()
{
	return Super::GetbIsInHardCC();
}

bool ACharacterController::GetbIsInSoftCC()
{
	return Super::GetbIsInSoftCC();
}

float ACharacterController::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (!bIsRolling &&  Effects != CharacterState::INVULNERABLE && Health > 0.f)
	{
		this->OnDamageRecieved.Broadcast();

		float NewHealth = Health;
		if (CurrentForm == TransformationState::WOLF)
		{
			NewHealth -= (DamageAmount * WolfDamageTakenMultiplier);
		}
		else
		{
			NewHealth -= DamageAmount;
		}

		if (NewHealth > MAXHEALTH)
		{
			NewHealth = MAXHEALTH;
		}

		UE_LOG(LogTemp, Display, TEXT("Player health modified was: %f, health is now: %f"), Health, NewHealth);

		Health = NewHealth;

		if (NewHealth <= 0.f)
		{
			Die();
		}
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

float ACharacterController::GetHealthPercent()
{
	return Super::GetHealthPercent();
}

AWeapon* ACharacterController::EquipNewWeapon(TSubclassOf<AWeapon> WeaponToEquip)
{
	CurrentlyEquippedWeapon = Super::EquipNewWeapon(WeaponToEquip);
	CurrentlyEquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("hand_r"));
	CurrentlyEquippedWeapon->SetActorLocation(GetMesh()->GetSocketLocation(FName("hand_r")));
	CurrentlyEquippedWeapon->SetActorRotation(FRotator::ZeroRotator);
	return CurrentlyEquippedWeapon;
}

CharacterState::StatusEffect ACharacterController::GetStatusEffect()
{
	return Effects;
}

void ACharacterController::OnMoveForward(float scale)
{
	if (!bIsRolling && !bIsInSoftCC)
	{
		if (scale > 0.02f)
		{
			if (LookDirection != MoveDirection)
			{
				OrientMeshToMovementDirection();
			}
			VerticalMove = 1;	
		}
		else if (scale < -0.02f)
		{
			if (LookDirection != MoveDirection)
			{
				OrientMeshToMovementDirection();
			}
			VerticalMove = -1;
		}
		else
		{
			VerticalMove = 0;
		}
		GetMovementComponent()->AddInputVector(GetActorForwardVector() * scale * MoveSpeedActual);
	}
}

void ACharacterController::OnMoveRight(float scale)
{
	if (!bIsRolling && !bIsInSoftCC)
	{
		if (scale > 0.f)
		{
			if (LookDirection != MoveDirection)
			{
				OrientMeshToMovementDirection();
			}
			HorizontalMove = 1;
		}
		else if (scale < 0.f)
		{
			if (LookDirection != MoveDirection)
			{
				OrientMeshToMovementDirection();
			}
			HorizontalMove = -1;
		}
		else
		{
			HorizontalMove = 0;
		}
		GetMovementComponent()->AddInputVector(GetActorRightVector() * scale * MoveSpeedActual);
	}
}

void ACharacterController::OnMouseMove(float scale)
{
	// Player controller class controls pawns, not where you'd want to store controls.
	if (!GetWorld()->IsPaused())
	{
		if (!bIsInHardCC && !bIsRolling)
		{
			if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
			{
				FVector2D MousePosition;
				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();

				if (ViewportClient && PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y))
				{
					FVector2D CenterPoint;
					PlayerController->ProjectWorldLocationToScreen(GetMesh()->GetComponentLocation(), CenterPoint);

					FVector Diff = FVector(MousePosition.X - CenterPoint.X, MousePosition.Y - CenterPoint.Y, 0.f);

					//GetMesh()->GetSocketRotation()
					AimOffsetYaw = Diff.Rotation().Yaw;
					DiffYaw = Diff.Rotation().Yaw;

					if (bRecenterMesh)
					{
						//UE_LOG(LogTemp, Display, TEXT("Mesh relative rotation Yaw: %f, AimOffSetYaw: %f"), GetMesh()->RelativeRotation.Yaw, AimOffsetYaw);
						GetMesh()->SetRelativeRotation(FMath::RInterpTo(GetMesh()->RelativeRotation, FRotator(0.f, AimOffsetYaw, 0.f), GetWorld()->GetDeltaSeconds(), TurnRate));
						if (GetMesh()->RelativeRotation.Yaw <= AimOffsetYaw + 25.f && GetMesh()->RelativeRotation.Yaw >= AimOffsetYaw - 25.f)
						{
							bRecenterMesh = false;
						}
					}
					if (CurrentForm == TransformationState::WOLF)
					{
						GetMesh()->SetRelativeRotation(FMath::RInterpTo(GetMesh()->RelativeRotation, FRotator(0.f, DiffYaw, 0.f), GetWorld()->GetDeltaSeconds(), TurnRate));
					}

					// Only adjust gun position if the player isn't reloading.
					if (!bShouldEnterReload)
					{
						if (CurrentlyEquippedWeapon != NULL && CurrentForm == TransformationState::HUMAN)
						{
							if (Cast<AWeapon_Ranged>(CurrentlyEquippedWeapon))
							{
								FRotator DesiredWeaponRotation = CurrentlyEquippedWeapon->GetActorRotation();
								FRotator OldRotation = CurrentlyEquippedWeapon->GetActorRotation();


								FHitResult OutHitResultResult(ForceInit);
								if (PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel6, false, OutHitResultResult))
								{
									FVector DirectionHorizontal = FVector(OutHitResultResult.Location.X - GetActorLocation().X, OutHitResultResult.Location.Y - GetActorLocation().Y, OutHitResultResult.Location.Z - GetActorLocation().Z);
									if (DirectionHorizontal.Size() > 140.f)
									{
										FVector Direction = OutHitResultResult.Location + FVector::UpVector * 128.f - CurrentlyEquippedWeapon->GetActorLocation();
										FRotator RotationInDirection = FRotationMatrix::MakeFromX(Direction).Rotator();
										DesiredWeaponRotation.Pitch = RotationInDirection.Pitch;
									}
									else
									{
										DesiredWeaponRotation.Pitch = 0.f;
									}

									if (DirectionHorizontal.Size() > 270.55f)
									{
										FRotator YawRotation = (OutHitResultResult.Location - CurrentlyEquippedWeapon->GetActorLocation()).Rotation();
										DesiredWeaponRotation.Yaw = YawRotation.Yaw;
									}
									else
									{
										DesiredWeaponRotation.Yaw = OldRotation.Yaw;
									}

									//FVector DirectionHorizontal = FVector(OutHitResultResult.Location.X - GetActorLocation().X, OutHitResultResult.Location.Y - GetActorLocation().Y, OutHitResultResult.Location.Z - GetActorLocation().Z);
								}
								else
								{
									//(GetActorLocation() + (GetMesh()->GetRightVector() * 256.f) - CurrentlyEquippedWeapon->GetActorLocation()).Rotation();
									DesiredWeaponRotation = OldRotation;
									DesiredWeaponRotation.Pitch = 0.f;
									DesiredWeaponRotation.Yaw = GetMesh()->RelativeRotation.Yaw;
									if (Diff.Size() > 50.f)
									{
										DesiredWeaponRotation.Yaw = Diff.Rotation().Yaw;
									}

								}

								DesiredWeaponRotation.Roll = 0.f;
								CurrentlyEquippedWeapon->SetActorRotation(FMath::RInterpTo(CurrentlyEquippedWeapon->GetActorRotation(), DesiredWeaponRotation, GetWorld()->GetDeltaSeconds(), TurnRate * TurnRate));

								if (GetMovementComponent()->GetLastInputVector() != FVector::ZeroVector)
								{
									//GetMesh()->SetRelativeRotation(FMath::RInterpTo(GetMesh()->RelativeRotation, FRotator(0.f, AimOffsetYaw, 0.f), GetWorld()->GetDeltaSeconds(), TurnRate));
								}
							}
						}
					}
				}
			}
		}
	}
}

void ACharacterController::OnInteractPressed()
{

}

void ACharacterController::OnInteractReleased()
{
	//if (!bIsInSoftCC)
	//{
	//	TArray<FOverlapResult> hitResult;
	//	GetWorld()->OverlapMultiByChannel(hitResult, GetActorLocation(), FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(50.f));
	//
	//	if (hitResult.Num() > 0)
	//	{
	//		if (AInteractable* Interactable = Cast<AInteractable>(hitResult[0].GetActor()))
	//		{
	//			Interactable->Interact(this);
	//			//UE_LOG(LogTemp, Display, TEXT("Actually hit a thing."));
	//		}
	//	}
	//}
}

void ACharacterController::OnRollPressed()
{
	if (!bIsInHardCC)
	{
		Roll();
		if (CurrentlyEquippedWeapon != NULL)
		{
			if (AWeapon_PlayerRevolver* RecastWeapon = Cast<AWeapon_PlayerRevolver>(CurrentlyEquippedWeapon))
			{
				RecastWeapon->StopFanFire();
			}
		}
	}
}

void ACharacterController::Roll()
{
	if (!bIsRolling)
	{
		FVector MovementVector = GetLastMovementInputVector();
		if (MovementVector != FVector::ZeroVector)
		{
			bIsRolling = true;
			RollDirection = MovementVector;

			FRotator RollRotator = GetMesh()->RelativeRotation;
			RollRotator.Yaw = (MovementVector.Rotation().Yaw + RollCompensationYaw);
			GetMesh()->SetRelativeRotation(RollRotator);
		}
		else
		{
			bIsRolling = true;
			InstantOrientToCursor();
			RollDirection = GetMesh()->GetRightVector();
		}
	}
}

void ACharacterController::OnReloadPressed()
{
	if (CurrentlyEquippedWeapon != NULL)
	{
		switch (CurrentForm)
		{
		case TransformationState::DEAD:
			break;
		case TransformationState::HUMAN:
			if (AWeapon_Ranged* RecastWeapon = Cast<AWeapon_Ranged>(CurrentlyEquippedWeapon))
			{
				if (AWeapon_PlayerRevolver* RecastAsRevolver = Cast<AWeapon_PlayerRevolver>(RecastWeapon))
				{
					RecastAsRevolver->StopFanFire();
				}
				if (RecastWeapon->CanReload())
				{
					bShouldEnterReload = true;
					if (OnSuccessfulReload.IsBound())
					{
						OnSuccessfulReload.Broadcast();
					}
				}
			}
		break;
	case TransformationState::WOLF:
		break;
	default:
		break;
		}
	}
	
}

void ACharacterController::OnTransformPressed()
{
	if (Rage >= MAXRAGE)
	{
		CurrentForm = TransformationState::WOLF;
		UE_LOG(LogTemp, Display, TEXT("Player transformed to wolf"));
	}
}

EightDirectional ACharacterController::GetRelativeFacing()
{
	return LookDirection;
}

EightDirectional ACharacterController::GetRelativeMovement()
{
	return MoveDirection;
}

void ACharacterController::SetAnimPrimaryFire(bool NewValue)
{
	bAnimPrimaryFire = NewValue;
}

void ACharacterController::SetAnimSecondaryFire(bool NewValue)
{
	bAnimSecondaryFire = NewValue;
}

void ACharacterController::SetShouldReload(bool NewValue)
{
	bShouldEnterReload = NewValue;
}

void ACharacterController::OnShootPressed()
{
	if (CurrentlyEquippedWeapon != NULL)
	{
		if (!bIsInHardCC && !bIsRolling && !bAnimSecondaryFire)
		{
			switch (CurrentForm)
			{
			case TransformationState::DEAD:
				break;
			case TransformationState::HUMAN:
				if (!bShouldEnterReload && CurrentlyEquippedWeapon->CanFire())
				{
					if (!bAnimPrimaryFire)
					{
						bAnimPrimaryFire = true;
						CurrentlyEquippedWeapon->Fire();
					}
					if (bAnimSecondaryFire)
					{
						bAnimSecondaryFire = false;
					}
				}
				break;
			case TransformationState::WOLF:
				if (!bIsMeleeAttacking && CurrentMeleeAttackType == UAttackTypes::NONE)
				{
					//UE_LOG(LogTemp, Display, TEXT("HEV"));
					bIsMeleeAttacking = true;
					CurrentMeleeAttackType = UAttackTypes::LIGHT;
				}
				break;
			default:
				break;
			}
		}
	}
}

void ACharacterController::OnShootReleased()
{

}

void ACharacterController::OnAltShootPressed()
{
	if (CurrentlyEquippedWeapon != NULL)
	{
		if (!bIsInHardCC && !bIsRolling)
		{
			switch (CurrentForm)
			{
			case TransformationState::DEAD:
				break;
			case TransformationState::HUMAN:
				if (!bShouldEnterReload)
				{
					bAnimPrimaryFire = false;
					bAnimSecondaryFire = true;
					CurrentlyEquippedWeapon->AltFire();
				}
				break;
			case TransformationState::WOLF:
				if (!bIsMeleeAttacking && CurrentMeleeAttackType == UAttackTypes::NONE)
				{
					//UE_LOG(LogTemp, Display, TEXT("HEV"));
					bIsMeleeAttacking = true;
					CurrentMeleeAttackType = UAttackTypes::HEAVY;
				}
				break;
			default:
				break;
			}
		}
	}
}

void ACharacterController::OnAltShootReleased()
{

}

void ACharacterController::OnDebugRagePressed()
{
	if (Rage <= MAXRAGE - 10.5f)
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
	//if (bIsRolling)
	//{
	//	RollDestination = RootComponent->RelativeLocation;
	//	bIsRolling = false;
	//}
}

void ACharacterController::OnAimSnapBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AAimSnapSurface* RecastedSurface = Cast<AAimSnapSurface>(OtherActor))
	{
		//DrawDebugLine(GetWorld(), GetActorLocation(), OtherActor->GetActorLocation(), FColor(0, 255, 0), false, 0.05f, 0, 12.333f);
		RecastedSurface->SetActive(true);
	}
}

void ACharacterController::OnAimSnapOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{	
	if (AAimSnapSurface* RecastedSurface = Cast<AAimSnapSurface>(OtherActor))
	{
		//DrawDebugLine(GetWorld(), GetActorLocation(), OtherActor->GetActorLocation(), FColor(255, 0, 0), false, 0.05f, 0, 12.333f);
		RecastedSurface->SetActive(false);
	}
}

void ACharacterController::InstantOrientToCursor()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		FVector2D MousePosition;
		UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();

		if (ViewportClient && PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y))
		{
			FVector2D CenterPoint;
			PlayerController->ProjectWorldLocationToScreen(GetMesh()->GetComponentLocation(), CenterPoint);

			FVector Diff = FVector(MousePosition.X - CenterPoint.X, MousePosition.Y - CenterPoint.Y, 0.f);

			GetMesh()->SetRelativeRotation(FRotator(0.f, Diff.Rotation().Yaw, 0.f));
		}
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

bool ACharacterController::bEnterReloadAnimation()
{
	return bShouldEnterReload;
}

void ACharacterController::Reload()
{
	if (CurrentForm == TransformationState::HUMAN)
	{
		if (CurrentlyEquippedWeapon != NULL)
		{
			if (AWeapon_Ranged* RecastPlayerWeapon = Cast<AWeapon_Ranged>(CurrentlyEquippedWeapon))
			{
				RecastPlayerWeapon->Reload();
				
			}
		}
	}
}

void ACharacterController::Die()
{
	Super::Die();
	CurrentForm = TransformationState::DEAD;
	if (APlayerController* RecastController = Cast<APlayerController>(GetController()))
	{
		DisableInput(RecastController);
		if (wDeadHud)
		{
			InGameHud->RemoveFromViewport();
			DeadHud = CreateWidget<UUserWidget>(GetWorld(), wDeadHud);
			if (!DeadHud->GetIsVisible())
			{
				DeadHud->AddToViewport(80);
				FInputModeUIOnly Mode;
				Mode.SetWidgetToFocus(DeadHud->GetCachedWidget());
				RecastController->SetInputMode(Mode);
				RecastController->bShowMouseCursor = true;
			}
		}
	}
}

void ACharacterController::TransformIntoWolf()
{
	if (WolfAnimationClass != NULL && WolfMesh != NULL)
	{
		if (bIsRolling)
		{
			bIsRolling = false;
		}
		if (GetMesh()->AnimClass != WolfAnimationClass)
		{
			WolfMesh = LoadObject<USkeletalMesh>(NULL, TEXT("SkeletalMesh'/Game/Geometry/Characters/Werewolf/SK_Werewolf.SK_Werewolf'"), NULL, LOAD_None, NULL);
			FString AnimClassStringWolf = "AnimBlueprint'/Game/Animation/Wolf/CharacterControllerWolf_AnimBP.CharacterControllerWolf_AnimBP_C'";
			WolfAnimationClass = LoadObject<UClass>(NULL, *AnimClassStringWolf);

			GetMesh()->SetAnimInstanceClass(WolfAnimationClass);
			//GetMesh()->GetAnimInstance

			if (GetMesh()->SkeletalMesh != WolfMesh)
			{
				GetMesh()->SetSkeletalMesh(WolfMesh);
			}

			if (UCharacterWolfAnimInstance* RecastAnimInstance = Cast<UCharacterWolfAnimInstance>(GetMesh()->GetAnimInstance()))
			{
				UE_LOG(LogTemp, Display, TEXT("The value that should force the exit animation to play was set!"));
				RecastAnimInstance->SetJustTransformed(true);
			}
		}

		if (CurrentlyEquippedWeapon != NULL)
		{
			DespawnCurrentWeapon();
			CurrentlyEquippedWeapon = NULL;
		}

		CurrentlyEquippedWeapon = GetWorld()->SpawnActor<AWeapon>(WolfWeapon);
		//CurrentlyEquippedWeapon->SetActorRelativeRotation(FRotator(90.f, 180.f, 0.f));
		CurrentlyEquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("rightclaw"));
		CurrentlyEquippedWeapon->SetOwner(this);
		GetWorld()->ForceGarbageCollection();
		UE_LOG(LogTemp, Display, TEXT("Transformation method resolved without causing a crash"));
	}
}

void ACharacterController::TransformIntoHuman()
{

	HumanMesh = LoadObject<USkeletalMesh>(NULL, TEXT("SkeletalMesh'/Game/Geometry/Characters/VincentArgo/SK_Vincent.SK_Vincent'"), NULL, LOAD_None, NULL);
	FString AnimClassStringHuman = "Class'/Game/Animation/Vincent/Character_Controller_AnimBP.Character_Controller_AnimBP_C'";
	HumanAnimationClass = LoadObject<UClass>(NULL, *AnimClassStringHuman);
	UE_LOG(LogTemp, Display, TEXT("Player 'Transformed' to human"));
	if (HumanAnimationClass && HumanMesh)
	{
		if (CurrentlyEquippedWeapon != NULL)
		{
			CurrentlyEquippedWeapon->SetLifeSpan(0.2f);
			CurrentlyEquippedWeapon = NULL;

		}
		CurrentMeleeAttackType = UAttackTypes::NONE;
		bIsMeleeAttacking = false;

		GetMesh()->SetAnimInstanceClass(HumanAnimationClass);
		GetMesh()->SetSkeletalMesh(HumanMesh);

		if (UCharacterHumanAnimInstance* RecastAnimInstance = Cast<UCharacterHumanAnimInstance>(GetMesh()->GetAnimInstance()))
		{
			RecastAnimInstance->SetJustTransformed(true);
		}

		GetWorld()->ForceGarbageCollection();

		if (CurrentlyEquippedWeapon == NULL)
		{
			CurrentlyEquippedWeapon = EquipNewWeapon(DefaultWeapon);
		}
	}
	Rage = 0.0f;
}

void ACharacterController::DespawnCurrentWeapon()
{
	if (CurrentlyEquippedWeapon != NULL)
	{
		if (AWeapon_Ranged* RecastAsRanged = Cast<AWeapon_Ranged>(CurrentlyEquippedWeapon))
		{
			if (AWeapon_PlayerRevolver* RecastAsRevolver = Cast<AWeapon_PlayerRevolver>(RecastAsRanged))
			{
				if (RecastAsRevolver->IsFanFiring())
				{
					RecastAsRevolver->StopFanFire();
				}
			}
			CurrentlyEquippedWeapon->SetLifeSpan(0.2f);
			CurrentlyEquippedWeapon = NULL;
			bShouldEnterReload = false;
			bAnimPrimaryFire = false;
			bAnimSecondaryFire = false;
		}
	}
}

void ACharacterController::RevokeControlAndBecomeInvulnerable()
{
	if (APlayerController* RecastController = Cast<APlayerController>(GetController()))
	{
		if (RecastController->IsValidLowLevel())
		{
			if (bIsRolling)
			{
				bIsRolling = false;
			}
			DisableInput(RecastController);
			Effects = CharacterState::INVULNERABLE;
		}
	}
	
}

void ACharacterController::RestoreControlAndRevokeInvulnerable()
{
	if (APlayerController* RecastController = Cast<APlayerController>(GetController()))
	{
		EnableInput(RecastController);
		Effects = CharacterState::NONE;
	}
}

void ACharacterController::OrientMeshToMovementDirection()
{
	switch (LookDirection)
	{
	case EightDirectional::NONE:
		//UE_LOG(LogTemp, Display, TEXT("NOPE"));
		break;
	case EightDirectional::RIGHT:
		GetMesh()->SetRelativeRotation(FMath::RInterpTo(GetMesh()->RelativeRotation, FRotator(0.f, 0.f, 0.f), GetWorld()->GetDeltaSeconds(), TurnRate));
		break;
	case EightDirectional::DOWN_RIGHT:
		GetMesh()->SetRelativeRotation(FMath::RInterpTo(GetMesh()->RelativeRotation, FRotator(0.f, 45.f, 0.f), GetWorld()->GetDeltaSeconds(), TurnRate));
		break;
	case EightDirectional::DOWN:
		GetMesh()->SetRelativeRotation(FMath::RInterpTo(GetMesh()->RelativeRotation, FRotator(0.f, 90.f, 0.f), GetWorld()->GetDeltaSeconds(), TurnRate));
		break;
	case EightDirectional::DOWN_LEFT:
		GetMesh()->SetRelativeRotation(FMath::RInterpTo(GetMesh()->RelativeRotation, FRotator(0.f, 135.f, 0.f), GetWorld()->GetDeltaSeconds(), TurnRate));
		break;
	case EightDirectional::LEFT:
		GetMesh()->SetRelativeRotation(FMath::RInterpTo(GetMesh()->RelativeRotation, FRotator(0.f, 180.f, 0.f), GetWorld()->GetDeltaSeconds(), TurnRate));
		break;
	case EightDirectional::UP_LEFT:
		GetMesh()->SetRelativeRotation(FMath::RInterpTo(GetMesh()->RelativeRotation, FRotator(0.f, 225.f, 0.f), GetWorld()->GetDeltaSeconds(), TurnRate));
		break;
	case EightDirectional::UP:
		GetMesh()->SetRelativeRotation(FMath::RInterpTo(GetMesh()->RelativeRotation, FRotator(0.f, 280.f, 0.f), GetWorld()->GetDeltaSeconds(), TurnRate));
		break;
	case EightDirectional::UP_RIGHT:
		GetMesh()->SetRelativeRotation(FMath::RInterpTo(GetMesh()->RelativeRotation, FRotator(0.f, 325.f, 0.f), GetWorld()->GetDeltaSeconds(), TurnRate));
		break;
	default:
		break;
	}
}

EightDirectional ACharacterController::RelativeFacingDirection(float Rotation)
{
	if (Rotation <= 22.5f || Rotation >= 337.5f)
	{
		/*if (Rotation <= 90.f && Rotation >= 0.f)
		{
			return EightDirectional::DOWN_RIGHT;
		}*/
		return EightDirectional::RIGHT;
	}
	if (Rotation <= 67.5f && Rotation >= 22.5f)
	{
		return EightDirectional::DOWN_RIGHT;
	}
	if (Rotation <= 113.5f && Rotation >= 67.5f)
	{
		return EightDirectional::DOWN;
	}
	if (Rotation <= 158.5f && Rotation >= 113.5f)
	{
		return EightDirectional::DOWN_LEFT;
	}
	if (Rotation <= 203.5f && Rotation >= 158.5f)
	{
		return EightDirectional::LEFT;
	}
	if (Rotation <= 248.5f && Rotation >= 203.5f)
	{
		return EightDirectional::UP_LEFT;
	}
	if (Rotation <= 293.5f && Rotation >= 248.5f)
	{
		return EightDirectional::UP;
	}
	if (Rotation <= 337.5f && Rotation >= 293.5f)
	{
		return EightDirectional::UP_RIGHT;
	}

	return EightDirectional::NONE;	
}

EightDirectional ACharacterController::RelativeMovementDirection()
{
	switch (VerticalMove)
	{
	case -1:
		switch (HorizontalMove)
		{
		case -1:
			return EightDirectional::DOWN_LEFT;
			break;
		case 1:
			return EightDirectional::DOWN_RIGHT;
			break;
		default:
			return EightDirectional::DOWN;
			break;
		}
		break;
	case 1:
		switch (HorizontalMove)
		{
		case -1:
			return EightDirectional::UP_LEFT;
			break;
		case 1:
			return EightDirectional::UP_RIGHT;
			break;
		default:
			return EightDirectional::UP;
			break;
		}
		break;
	default:
		switch (HorizontalMove)
		{
		case -1:
			return EightDirectional::LEFT;
			break;
		case 1:
			return EightDirectional::RIGHT;
			break;
		default:
			return EightDirectional::NONE;
			break;
		}
		break;
	}
}

TransformationState ACharacterController::GetCurrentForm()
{
	return CurrentForm;
}
