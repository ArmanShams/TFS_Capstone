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
#include "Character/PlayerCharacter/CharacterController.h"
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
	AttackRange = 650.f;
	MaximumTrapsAllowed = 3;
	CushionSpace = 250.f;
	PatrolDistance = 1000.f;
	SearchingLocations = 1100.f;
	bPlayRecoilAnimation = false;
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
}

void ABountyHunter::BeginPlay()
{
	Super::BeginPlay();
	EquipNewWeapon(DefaultWeapon);
}

void ABountyHunter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (bPlayRecoilAnimation)
	{
		bPlayRecoilAnimation = false;
	}

	if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
	{
		BlackboardComponent->SetValueAsBool(TEXT("IsHardCC"), bIsInHardCC);
		BlackboardComponent->SetValueAsBool(TEXT("IsSoftCC"), bIsInSoftCC);
		BlackboardComponent->SetValueAsBool(TEXT("CanAttack"), bCanAttack());
		BlackboardComponent->SetValueAsBool(TEXT("IsAttack"), bIsAttacking);
		BlackboardComponent->SetValueAsBool(TEXT("IsAiming"), bIsAiming);
		BlackboardComponent->SetValueAsBool(TEXT("IsInPatrollingRange"), bIsInRange(PatrolDistance));
		BlackboardComponent->SetValueAsBool(TEXT("IsInSearchingLocationRange"), bIsInRange(SearchingLocations));
		BlackboardComponent->SetValueAsBool(TEXT("bSafeAttackingDistance"), bSafeAttackingDistance());
		BlackboardComponent->SetValueAsEnum(TEXT("StatusEffects"), Effects);
		BlackboardComponent->SetValueAsEnum(TEXT("CurrentState"), (uint8)CurrentState);
		BlackboardComponent->SetValueAsObject(TEXT("FirstTargetLocation"), FirstTrapLocation);
		BlackboardComponent->SetValueAsObject(TEXT("FirstTargetLocation"), SecondTrapLocation);
		BlackboardComponent->SetValueAsObject(TEXT("FirstTargetLocation"), ThirdTrapLocation);

		
		bIsFlee();
		bCanAttack();
		bIsPatrolling();
		bSearchingTrapLocations();

		if (BlackboardComponent->GetValueAsObject(TEXT("Target")) != NULL)
		{
			if (ACharacterController* RecastedTarget = Cast<ACharacterController>GetActor())
			{
				FVector CurrentLocation = GetActorLocation();
				FVector PlayerLocation = RecastedTarget->GetActorLocation();
				FVector Direction = CurrentLocation - PlayerLocation;
				float Distance = FVector::Dist(CurrentLocation, PlayerLocation); //  UE_LOG(LogTemp, Display, TEXT("Distance: %f"), Distance);
				switch (CurrentState)
				{
				case BountyHunterState::IDLE:
					break;
				case BountyHunterState::AIMING:
					//bIsAiming = true;
					FixWeaponRotation();
					break;
				case BountyHunterState::ATTACKING:
					//bIsAttacking = true;
					Attack();
					break;
				case BountyHunterState::FLEEING:
					Flee(RecastedTarget);
					break;
				case BountyHunterState::SETTINGTRAP:
					break;
				case BountyHunterState::HARDCC:
					break;
				case BountyHunterState::PATROLLING:
					break;
				case BountyHunterState::SEARCHFORTRAPLOCATIONS:
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
	return Super::bIsInRange(AttackRange);
}

bool ABountyHunter::bIsInRange(float OveriddenDesiredRange)
{
	return Super::bIsInRange(OveriddenDesiredRange);
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


bool ABountyHunter::bCanTriggerRecoilAnimation()
{
	return bPlayRecoilAnimation;
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
	return Super::Die();
}

//bool ABountyHunter::GetBTIsInRange()
//{
//	if (HasActorBegunPlay() && CurrentState == BountyHunterState::ATTACKING)
//	{
//		UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent();
//		return BlackboardComponent->GetValueAsBool(TEXT("IsInMeleeRange"));
//	}
//	return false;
//}

AWeapon* ABountyHunter::EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip)
{
	CurrentlyEquippedWeapon = Super::EquipNewWeapon(WeaponToEquip);
	CurrentlyEquippedWeapon->SetActorRelativeRotation(FRotator(30.f, -90.f, 90.f));
	return CurrentlyEquippedWeapon;
}

void ABountyHunter::SetBearTrap(ATrapLocations* NewTrapLocation, const FHitResult& SweepResult)
{
	if (CurrentState == BountyHunterState::SETTINGTRAP && !NewTrapLocation->bIsOccupied)
	{ // bSetTrap();
		UE_LOG(LogTemp, Display, TEXT("The trap location is now occupied"));
		if (BearTrapClass != NULL)
		{
			if (TrapArray.Num() >= MaximumTrapsAllowed)
			{
				AActor* TrapToDelete = TrapArray.Pop();
				TrapToDelete->SetLifeSpan(0.1f);
				//UE_LOG(LogTemp, Display, TEXT("Element popped from Trap Array"));
			}
			BearTrapPlaced = GetWorld()->SpawnActor<ABearTrap>(BearTrapClass);
			BearTrapPlaced->SetActorRelativeLocation(GetMesh()->GetSocketLocation("TrapBone"));
			BearTrapPlaced->SetOwner(this);
			NewTrapLocation->bIsOccupied = true;
			BearTrapPlaced->SetLocationBeingOccupied(NewTrapLocation);
			TrapArray.Add(BearTrapPlaced);
			UE_LOG(LogTemp, Display, TEXT("Bounty Hunter set a bear trap, trap added to array list"));
		}
		else
		{ // bSetTrap();
		  //UE_LOG(LogTemp, Display, TEXT("The Trap Location is already occupied, the bounty hunter will not try to place a trap here"));
			bPlacingTrap = false;
		}
	}
}

void ABountyHunter::OnActorBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if (ATrapLocations* RecastedOverlappingActor = Cast<ATrapLocations>(OtherActor))
	{
		if (RecastedOverlappingActor->bIsOccupied == false)
		{
			CurrentState = BountyHunterState::SETTINGTRAP;
			bPlacingTrap = true;
			SetBearTrap(RecastedOverlappingActor, SweepResult);
		}
	}
}

bool ABountyHunter::bSafeAttackingDistance()
{
	if (bCanAttack() && !bIsFlee())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("bSafeAttackingDistance = true!")));
		//UE_LOG(LogTemp, Display, TEXT("bCanAttack = true"));
		return true;
	}
	return false;
}

bool ABountyHunter::bCanAttack()
{
	if (bIsInRange(AttackRange)) 
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, FString::Printf(TEXT("CanAttack = true!")));
		return true;
	}
	return false;
}

bool ABountyHunter::bSearchingTrapLocations()
{
	if (bIsInRange(SearchingLocations))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("bSearchingTrapLocations = true!")));
		return true;
	}
	return false;
}

bool ABountyHunter::bIsPatrolling()
{
	if (bIsInRange(PatrolDistance))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("bIsPatrolling = true!")));
		return true;
	}
	return false;
}

bool ABountyHunter::bIsFlee()
{
	if (bIsInRange(CushionSpace))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("Fleeing!")));
		CurrentState = BountyHunterState::FLEEING;
		return true;
	}
	return false;
}

void ABountyHunter::Attack()
{
	if (CurrentlyEquippedWeapon != NULL)
	{
		if (CurrentlyEquippedWeapon->CanFire())
		{
			FixWeaponRotation();
			CurrentlyEquippedWeapon->Fire();
			bPlayRecoilAnimation = true;
			bPlacingTrap = false;
		}
	}
}

void ABountyHunter::Flee(ACharacterController* PlayerToFleeFrom)
{

	FVector CurrentLocation = GetActorLocation();
	FVector PlayerLocation = PlayerToFleeFrom->GetActorLocation();
	FRotator RotationToPlayer = PlayerToFleeFrom->GetActorRotation();
	FVector Direction = CurrentLocation - PlayerLocation;
	float DistanceToPlayer = FVector::Dist(CurrentLocation, PlayerLocation);
	if (DistanceToPlayer <= (CushionSpace + 50.f))
	{
		//SetBountyHunterState(BountyHunterState::FLEEING);
		bIsAiming = false;
		//if (bIsAtacking == false)
		//{
		//	GetMovementComponent()->AddInputVector(DistanceToPlayer * Direction);

		//}
		//GEngine->AddOnScreenDebugMessage(-1, 1.f , FColor::Red, FString::Printf(TEXT("BountyHunter in the beam")));
	}
	if (DistanceToPlayer > CushionSpace)
	{
		bIsFleeing = false;	
		//SetBountyHunterState(BountyHunterState::AIMING);
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