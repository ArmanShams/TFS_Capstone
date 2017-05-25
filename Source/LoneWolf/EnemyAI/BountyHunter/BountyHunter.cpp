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
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABountyHunter::OnActorBeginOverlap);

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

	ConstructorHelpers::FClassFinder<AActor>AimLineDecalActor(TEXT("Blueprint'/Game/Blueprints/Enemies/BountyHunterAI/AimingDecal.AimingDecal_C'"));
	if (AimLineDecalActor.Class)
	{
		AimLineDecalClass = (UClass*)AimLineDecalActor.Class;
	}
}

void ABountyHunter::BeginPlay()
{
	Super::BeginPlay();
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
		BlackboardComponent->SetValueAsBool(TEXT("CanAttack"), bCanAttack);			// bCanBasicAttack
		BlackboardComponent->SetValueAsBool(TEXT("IsAttack"), bIsAttacking);		// bIsBasicAttack
		BlackboardComponent->SetValueAsBool(TEXT("IsAiming"), bIsAiming);			// bIsAiming
		BlackboardComponent->SetValueAsBool(TEXT("IsSettingTrap"), bPlacingTrap);	// bCanSetTrap = bPlacingTrap

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

		if (!bIsInRange(AttackRange))
		{
			//if (UBehaviorTreeComponent& OwnerComp)
			//{
			//	UAIPerceptionComponent* PerceptionComponent = OwnerComp.GetAIOwner()->GetPerceptionComponent();
			//	PerceptionComponent->GetHostileActors(0);
			//}
		}

		if (BlackboardComponent->GetValueAsObject(TEXT("Target")) != NULL)
		{
			if (ACharacterController* RecastedTarget = Cast<ACharacterController>(BlackboardComponent->GetValueAsObject(TEXT("Target"))))
			{
				switch (CurrentState)
				{
				case BountyHunterState::IDLE:
					bIsAiming = false;
					bPlacingTrap = false;
					bIsAttacking = false;
					break;
				case BountyHunterState::AIMING:
					bIsAiming = true;
					Aim(RecastedTarget);
					break;
				case BountyHunterState::ATTACKING:
					bCanAttack = true;
					bIsAiming = false;
					Aim(RecastedTarget);
					Attack();
					bIsAttacking = true;
					break;
				case BountyHunterState::FLEEING:
					if (bIsAiming == false && !bIsInHardCC)
					{
						if (bIsAttacking == false)
						{
							bCanAttack = false;
							bPlacingTrap = false;
							Flee(RecastedTarget);
						}
					}
					break;
				case BountyHunterState::SETTINGTRAP:
					break;
				case BountyHunterState::HARDCC:
					break;
				default:
					break;
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
	float DesiredRange = OveriddenDesiredRange;
	FVector CurrentLocation = GetActorLocation();
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();

	const float CurrentDistance = FVector::Dist(PlayerLocation, CurrentLocation);

	if (CurrentDistance > CushionSpace && CurrentDistance <= AttackRange)
	{
		DrawDebugLine(GetWorld(), CurrentLocation, PlayerLocation, FColor::White, false, -1, 0, 12.333);
		bAttack = true;
		bFlee = false;
		bPlacingTrap = false;
	}

	if (CurrentDistance < CushionSpace)
	{
		DrawDebugLine(GetWorld(), CurrentLocation, PlayerLocation, FColor::Red, false, -1, 0, 12.333);
		bAttack = false;
		bFlee = true;

		//bPatrol = false;
		bCanAttack = false;
		bIsFleeing = true;

	}

	if (CurrentDistance > AttackRange)
	{
		//bPatrol = true;
		bFlee = false;
		bAttack = false;

		//UE_LOG(LogTemp, Display, TEXT("Distance: %f"), CurrentDistance);
		bCanAttack = false;
		bIsFleeing = false;
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
	if (AimLineDecalActor != NULL)
	{ UE_LOG(LogTemp, Display, TEXT("Aiming Line Decal actor successfully DE-Stroyed"));
		AimLineDecalActor->SetOwner(NULL);
		AimLineDecalActor->SetLifeSpan(0.001f);
		AimLineDecalActor = NULL;
	}
	return Super::Die();
}

AWeapon* ABountyHunter::EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip)
{
	CurrentlyEquippedWeapon = Super::EquipNewWeapon(WeaponToEquip);
	CurrentlyEquippedWeapon->SetActorRelativeRotation(FRotator(30.f, -90.f, 90.f));
	return CurrentlyEquippedWeapon;
}

void ABountyHunter::SetBearTrap(ATrapLocations* NewTrapLocation, const FHitResult& SweepResult)
{
	if (CurrentState == BountyHunterState::SETTINGTRAP && !NewTrapLocation->bIsOccupied)
	{ UE_LOG(LogTemp, Display, TEXT("The trap location is now occupied"));
		if (BearTrapClass != NULL)
		{ UE_LOG(LogTemp, Display, TEXT("Bounty Hunter set a bear trap, trap added to array list"));
			if (TrapArray.Num() >= MaximumTrapsAllowed)
			{ UE_LOG(LogTemp, Display, TEXT("Element popped from Trap Array"));
				AActor* TrapToDelete = TrapArray.Pop();
				TrapToDelete->SetLifeSpan(0.1f);
			}
			BearTrapPlaced = GetWorld()->SpawnActor<ABearTrap>(BearTrapClass);
			BearTrapPlaced->SetActorRelativeLocation(GetMesh()->GetSocketLocation("TrapBone"));
			BearTrapPlaced->SetOwner(this);
			NewTrapLocation->bIsOccupied = true;
			BearTrapPlaced->SetLocationBeingOccupied(NewTrapLocation);
			TrapArray.Add(BearTrapPlaced);
		}
		else
		{ UE_LOG(LogTemp, Display, TEXT("The Trap Location is already occupied, the bounty hunter will not try to place a trap here"));
			bPlacingTrap = false;	// Animation Variable: bCanSetTrap = false;
		}
	}
	if (CurrentState != BountyHunterState::SETTINGTRAP)
	{
		UE_LOG(LogTemp, Display, TEXT("Checked for current state, and could not set trap"));
	}
}

void ABountyHunter::OnActorBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (ATrapLocations* RecastedOverlappingActor = Cast<ATrapLocations>(OtherActor))
	{
		if (RecastedOverlappingActor->bIsOccupied == false)
		{
			bPlacingTrap = true; // Animation Variable: bCanSetTrap = true;
			SetBearTrap(RecastedOverlappingActor, SweepResult);
		}
		if (RecastedOverlappingActor->bIsOccupied == true)
		{
			SetBountyHunterState(BountyHunterState::IDLE);
		}
	}
}

void ABountyHunter::Aim(ACharacterController* PlayerRecasted)
{
	FixWeaponRotation();
	FVector Direction = PlayerRecasted->GetActorLocation() - GetActorLocation();
	//FRotator NewYawRotation = (PlayerToAimAt->GetActorLocation() - GetActorLocation()).Rotation();
	//FRotator NewPitchRotation = PlayerToAimAt->GetActorRotation();
	FRotator NewRollRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	SetActorRotation(NewRollRotation);
}

void ABountyHunter::Attack()
{
	if (CurrentlyEquippedWeapon != NULL)
	{
		if (CurrentlyEquippedWeapon->CanFire())
		{
			FixWeaponRotation();
			//CurrentlyEquippedWeapon->Fire();
		}

	}
}

void ABountyHunter::Flee(ACharacterController* PlayerRecasted)
{
	//SetBountyHunterState(BountyHunterState::IDLE);
	FVector CurrentLocation = GetActorLocation();
	FVector PlayerLocation = PlayerRecasted->GetActorLocation();
	FRotator RotationToPlayer = PlayerRecasted->GetActorRotation();
	FVector Direction = CurrentLocation - PlayerLocation;

	float DistanceToPlayer = FVector::Dist(CurrentLocation, PlayerLocation);
		
	if (CurrentState == BountyHunterState::FLEEING)
	{
		SetActorRotation(Direction.Rotation());
		GetMovementComponent()->AddInputVector(DistanceToPlayer * Direction);
	}

	if (DistanceToPlayer > CushionSpace)
	{
		bIsFleeing = false;
	}
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