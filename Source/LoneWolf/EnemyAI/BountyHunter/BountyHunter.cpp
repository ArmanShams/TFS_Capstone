// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "Environment/BearTrap.h"
#include "TrapLocations.h"
#include "BountyHunter.h"
#include "Engine.h"
#include "Weapons/Weapon.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BrainComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Character/PlayerCharacter/CharacterController.h"
#include "EnemyAI/BountyHunter/BountyHunterAIController.h"
#include "Character/StatusEffects/StatusEffect_HardCrowdControl.h"

ABountyHunter::ABountyHunter()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = GetCapsuleComponent();
	GetMesh()->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	Health = MAXHEALTH;
	MoveSpeed = .01f;
	TurnRate = 0.25f;
	MaxRange = 300.f;
	AttackFrequency = 1.f;
	AttackRange = 500.f;
	MaximumTrapsAllowed = 3;
	CushionSpace = 275.f;

	CurrentState = BountyHunterState::IDLE;

	ConstructorHelpers::FClassFinder<AWeapon>WeaponAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/Weapon_RifleBP.Weapon_RifleBP_C'"));
	if (WeaponAsset.Class)
	{
		DefaultWeapon = (UClass*)WeaponAsset.Class;
	}

	ConstructorHelpers::FClassFinder<ABearTrap>TrapAsset(TEXT("Blueprint'/Game/Blueprints/Enemies/BountyHunterAI/BearTrapBP.BearTrapBP_C'"));
	if (TrapAsset.Class)
	{
		BearTrapClass = (UClass*)TrapAsset.Class;
	}
	//ConstructorHelpers::FClassFinder<AActor>AimLineDecalAsset(TEXT("Blueprint'/Game/Blueprints/Enemies/BountyHunterAI/AimingDecal.AimingDecal_C'"));
	//if (AimLineDecalAsset.Class)
	//{
	//	AimLineDecalClass = (UClass*)AimLineDecalAsset.Class;
	//}
}

void ABountyHunter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABountyHunter::OnComponentOverlap);
	EquipNewWeapon(DefaultWeapon);
}

void ABountyHunter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
	{
		//Animation																	Variables:
		BlackboardComponent->SetValueAsBool(TEXT("IsHardCC"), bIsInHardCC);			// bIsHardCC
		BlackboardComponent->SetValueAsBool(TEXT("IsSoftCC"), bIsInSoftCC);			// bIsSoftCC

		//Checking the range
		BlackboardComponent->SetValueAsBool(TEXT("bIsInFleeRange"), bFlee);
		BlackboardComponent->SetValueAsBool(TEXT("bIsInAttackRange"), bAttack);
		BlackboardComponent->SetValueAsBool(TEXT("bIsInPatrolRange"), bPatrol);

		//Check for status
		BlackboardComponent->SetValueAsEnum(TEXT("StatusEffects"), Effects);
		BlackboardComponent->SetValueAsEnum(TEXT("CurrentState"), (uint8)CurrentState);

		//When patrolling, set target locations, if NULL, set searching for trap locations to false
		BlackboardComponent->SetValueAsObject(TEXT("FirstTargetLocation"), NULL);
		BlackboardComponent->SetValueAsObject(TEXT("SecondTargetLocation"), NULL);
		BlackboardComponent->SetValueAsObject(TEXT("ThirdTargetLocation"), NULL);

		if (BlackboardComponent->GetValueAsObject(TEXT("Target")) != NULL)
		{
			if (ACharacterController* RecastedTarget = Cast<ACharacterController>(BlackboardComponent->GetValueAsObject(TEXT("Target"))))
			{
				bIsInRange(AttackRange);


				switch (CurrentState)
				{
				case BountyHunterState::IDLE:		
					break;
				case BountyHunterState::AIMING:
					FixWeaponRotation();
					DrawDebugLine(GetWorld(), GetActorLocation(), RecastedTarget->GetActorLocation(), FColor::Red, false, 0.05f, 1.f, 5.f);
					break;
				case BountyHunterState::ATTACKING:
					break;
				case BountyHunterState::FLEEING:
					CurrentLocation = GetActorLocation();
					PlayerLocation = RecastedTarget->GetActorLocation();
					RotationToPlayer = RecastedTarget->GetActorRotation();
					Direction = -1.f * (PlayerLocation - CurrentLocation).GetSafeNormal();
					DistanceToPlayer = FVector::Dist(CurrentLocation, PlayerLocation);
					Rotator = GetActorRotation();
					Rotator.Yaw = Direction.Rotation().Yaw;
					SetActorRotation(Rotator);
					if (DistanceToPlayer > CushionSpace)
					{
						bIsFleeing = false;
						SetBountyHunterState(BountyHunterState::IDLE);
					}
					break;
				case BountyHunterState::HARDCC:
					break;
				case BountyHunterState::SETTINGTRAP:
					break;
				default:
					break;
				}

				if (bShouldAdjustGun)
				{
					Aim(RecastedTarget);
				}
			}
		}
	}
}

float ABountyHunter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ABountyHunter::SetupPlayerInputComponent(class UInputComponent* InInputComponent)
{
	Super::SetupPlayerInputComponent(InInputComponent);
}

void ABountyHunter::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::AddStatusEffect(ClassToCreateFrom, bShouldPerformTickAction, LifeTime, TickRate, CharacterThatInflictedStatusEffect);
}

void ABountyHunter::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, bool bShouldDealDamage, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::AddStatusEffect(ClassToCreateFrom, bShouldPerformTickAction, bShouldDealDamage, LifeTime, DamageToDeal, TickRate, CharacterThatInflictedStatusEffect);
}

AWeapon* ABountyHunter::GetEquippedWeapon()
{
	return Super::GetEquippedWeapon();
}

bool ABountyHunter::bIsInRange()
{
	
	return bIsInRange(AttackRange);
}

bool ABountyHunter::bIsInRange(float OveriddenDesiredRange)
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter != NULL)
	{
		float DesiredRange = OveriddenDesiredRange;
		FVector CurrentLocation = GetActorLocation();
		FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		const float CurrentDistance = FVector::Dist(PlayerLocation, CurrentLocation);

		if (CurrentDistance > CushionSpace && CurrentDistance <= AttackRange)
		{ //DrawDebugLine(GetWorld(), CurrentLocation, PlayerLocation, FColor::White, false, -1, 0, 12.333);
			bAttack = true;
			bFlee = false;
			bPatrol = false;
		}

		if (CurrentDistance < CushionSpace)
		{ //DrawDebugLine(GetWorld(), CurrentLocation, PlayerLocation, FColor::Red, false, -1, 0, 12.333;
			bAttack = false;
			bFlee = true;
			bPatrol = false;
		}

		if (CurrentDistance > AttackRange)
		{
			bPatrol = true;
			bFlee = false;
			bAttack = false;
		}
	}
	if (PlayerCharacter == NULL)
	{
		UE_LOG(LogTemp, Display, TEXT("WE ARE NOT IN THE BEAM"));
	}
	return false;
}

CharacterState::StatusEffect ABountyHunter::GetStatusEffect()
{
	return Super::GetStatusEffect();
}

bool ABountyHunter::GetbIsInHardCC()
{
	return Super::GetbIsInHardCC();
}

bool ABountyHunter::GetbIsInSoftCC()
{
	return Super::GetbIsInSoftCC();
}

bool ABountyHunter::bIsSoftCC()
{
	return Super::bIsSoftCC();
}

bool ABountyHunter::bIsHardCC()
{
	return Super::bIsHardCC();
}

void ABountyHunter::Destroyed()
{
	Super::Destroyed();
}

void ABountyHunter::SetBountyHunterState(BountyHunterState NewState)
{
	CurrentState = NewState;
}

BountyHunterState ABountyHunter::GetBountyHunterState()
{
	return CurrentState;
}

void ABountyHunter::Die()
{
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		if (UBrainComponent* BrainComponent = AIController->GetBrainComponent())
		{
			BrainComponent->StopLogic(FString("An enemy died, stopping logic."));
			GetCapsuleComponent()->SetCollisionProfileName(FName("NoCollision"));
		}
	}
	return Super::Die();
}

AWeapon* ABountyHunter::EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip)
{
	CurrentlyEquippedWeapon = Super::EquipNewWeapon(WeaponToEquip);
	CurrentlyEquippedWeapon->SetActorRelativeRotation(FRotator(-4.5f, 175.f, -22.f));
	CurrentlyEquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("hand_r"));
	return CurrentlyEquippedWeapon;
}

void ABountyHunter::SetBearTrap(ATrapLocations* NewTrapLocation, const FHitResult& SweepResult)
{
	if (CurrentState == BountyHunterState::SETTINGTRAP)
	{
		if (!NewTrapLocation->bIsOccupied)
		{
			UE_LOG(LogTemp, Display, TEXT("The trap location is now occupied"));
			if (BearTrapClass != NULL)
			{
				UE_LOG(LogTemp, Display, TEXT("Bounty Hunter set a bear trap, trap added to array list"));
				if (TrapArray.Num() > MaximumTrapsAllowed)
				{
					UE_LOG(LogTemp, Display, TEXT("Element popped from Trap Array"));
					AActor* TrapToDelete = TrapArray[0];
					TrapArray.RemoveAt(0, 1, false);
					TrapToDelete->SetLifeSpan(0.1f);
				}
				//NewTrapLocation->bIsOccupied = true;
				bIsPlacingTrap = true;
				BearTrapPlaced = GetWorld()->SpawnActor<ABearTrap>(BearTrapClass);
				BearTrapPlaced->AttachToActor(NewTrapLocation, FAttachmentTransformRules::KeepRelativeTransform);
				BearTrapPlaced->SetActorRelativeLocation(FVector::ZeroVector);
				BearTrapPlaced->SetLocationBeingOccupied(NewTrapLocation);
				BearTrapPlaced->SetOwner(this);
				TrapArray.Add(BearTrapPlaced);
			}
		}
	}
}

void ABountyHunter::DecrementActiveBearTraps(ABearTrap* TrapToRemove)
{
	if (TrapArray.Contains(TrapToRemove))
	{
		AActor* TrapToDelete = TrapToRemove;
		TrapArray.RemoveSingle(TrapToRemove);
		TrapToDelete->SetLifeSpan(0.1f);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("Removed element from array.")));
	}
}

void ABountyHunter::OnComponentOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (ATrapLocations* RecastedOverlappingActor = Cast<ATrapLocations>(OtherActor))
	{
		if (!RecastedOverlappingActor->bIsOccupied)
		{
			SetBearTrap(RecastedOverlappingActor, SweepResult);
		}
		if (RecastedOverlappingActor->bIsOccupied)
		{
			SetBountyHunterState(BountyHunterState::IDLE);
		}
	}
}

void ABountyHunter::Aim(ACharacterController* Player)
{
	FixWeaponRotation();
	FVector Direction = Player->GetActorLocation() - GetActorLocation();
	FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	SetActorRotation(NewRotation);
}

void ABountyHunter::Attack()
{
	CurrentlyEquippedWeapon->Fire();
}

void ABountyHunter::FixWeaponRotation()
{
	if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
	{
		if (BlackboardComponent->GetValueAsObject(TEXT("Target")) != NULL)
		{
			if (ACharacterController* RecastTarget = Cast<ACharacterController>(BlackboardComponent->GetValueAsObject(TEXT("Target"))))
			{
				if (CurrentlyEquippedWeapon != NULL)
				{
					FRotator DesiredWeaponRotation = GetActorRotation();
					FVector DirectionToTarget = RecastTarget->GetActorLocation() - GetActorLocation();
					if (DirectionToTarget.Size() > 300.f)
					{
						FRotator YawRotation = (RecastTarget->GetActorLocation() - CurrentlyEquippedWeapon->GetActorLocation()).Rotation();
						DesiredWeaponRotation.Yaw = YawRotation.Yaw;
					}
					else
					{
						FRotator YawRotation = (GetActorLocation() + (GetMesh()->GetRightVector() * 256.f) - CurrentlyEquippedWeapon->GetActorLocation()).Rotation();

						DesiredWeaponRotation.Yaw = YawRotation.Yaw;
					}
					FRotator RotationInDirection = FRotationMatrix::MakeFromX(DirectionToTarget).Rotator();
					DesiredWeaponRotation.Pitch = RotationInDirection.Pitch;

					CurrentlyEquippedWeapon->SetActorRotation(FMath::RInterpTo(CurrentlyEquippedWeapon->GetActorRotation(), DesiredWeaponRotation, GetWorld()->GetDeltaSeconds(), 200.f));
				}
			}
		}
	}
}