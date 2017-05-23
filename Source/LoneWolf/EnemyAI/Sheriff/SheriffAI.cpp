// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "SheriffAnimInstance.h"
#include "SheriffAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Character/PlayerCharacter/CharacterController.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BrainComponent.h"
#include "CableComponent.h"
#include "Character/StatusEffects/StatusEffect_SoftCrowdControl.h"
#include "SheriffAI.h"

ASheriffAI::ASheriffAI()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Health = MAXHEALTH;
	MoveSpeed = 1.0f;
	TurnRate = 0.25f;
	MaxRange = 100.0f;
	AttackFrequency = 5.f;
	AttackRange = 500.0f;
	PullingForce = 0.005f;
	LassoLength = 100.f;
	KnifeAttackRange = 75.0f;
	RevolverAttackRange = 125.0f;
	LassoAttackRange = 175.0f;

	FName LassoSocket = TEXT("hand_r");
	LassoCableComponent = CreateDefaultSubobject<UCableComponent>(TEXT("Cable Component"));
	LassoCableComponent->AttachTo(GetMesh(), LassoSocket);

	ConstructorHelpers::FClassFinder<AWeapon>KnifeAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/KnifeBP_Arman.KnifeBP_Arman_C'"));
	if (KnifeAsset.Class)
	{
		KnifeWeapon = (UClass*)KnifeAsset.Class;
	}

	ConstructorHelpers::FClassFinder<AWeapon>ShotgunAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/Sheriff/SheriffShotgunBP.SheriffShotgunBP_C'"));
	if (ShotgunAsset.Class)
	{
		ShotgunWeapon = (UClass*)ShotgunAsset.Class;
	}

	ConstructorHelpers::FClassFinder<AActor>LassoAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/LassoBP.LassoBP_C'"));
	if (LassoAsset.Class)
	{
		UE_LOG(LogTemp, Display, TEXT("We have found the lasso!"));
		LassoWeapon = (UClass*)LassoAsset.Class;
	}

	DefaultWeapon = ShotgunWeapon;
}

void ASheriffAI::BeginPlay()
{

}

void ASheriffAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
	{
		//Animation																	Variables:
		BlackboardComponent->SetValueAsBool(TEXT("IsHardCC"), bIsInHardCC);			// bIsHardCC
		BlackboardComponent->SetValueAsBool(TEXT("IsSoftCC"), bIsInSoftCC);			// bIsSoftCC
		BlackboardComponent->SetValueAsBool(TEXT("CanAttack"), bCanAttack);			// bCanBasicAttack
		BlackboardComponent->SetValueAsBool(TEXT("IsAttack"), bIsBasicAttack);		// bIsBasicAttack
		BlackboardComponent->SetValueAsBool(TEXT("IsAiming"), bIsAiming);			// bIsAiming
		BlackboardComponent->SetValueAsBool(TEXT("SwingingKnife"), bIsBasicAttack); // NOT IMPLEMENTED

		//Checking the range
		BlackboardComponent->SetValueAsBool(TEXT("IsInAttackRange"), bIsInRange(AttackRange));
		BlackboardComponent->SetValueAsBool(TEXT("bSafeAttackingDistance"), bSafeAttackingDistance());

		//Check for status
		BlackboardComponent->SetValueAsEnum(TEXT("StatusEffects"), Effects);
		BlackboardComponent->SetValueAsEnum(TEXT("CurrentState"), (uint8)CurrentState);

		if (BlackboardComponent->GetValueAsObject(TEXT("Target")) != NULL)
		{
			switch (CurrentState)
			{
			case SheriffState::IDLE:
				break;
			case SheriffState::MELEE:
				break;
			case SheriffState::RANGED:
				break;
			case SheriffState::CASTING:
				break;
			case SheriffState::LASSO:
				break;
			case SheriffState::HARDCC:
				break;
			default:
				UE_LOG(LogTemp, Display, TEXT("There's been an error in setting the state of the Sheriff"));
				break;
			}
		}
	}
}

float ASheriffAI::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ASheriffAI::SetupPlayerInputComponent(class UInputComponent* InInputComponent)
{
	Super::SetupPlayerInputComponent(InInputComponent);
}

void ASheriffAI::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::AddStatusEffect(ClassToCreateFrom, bShouldPerformTickAction, LifeTime, TickRate, CharacterThatInflictedStatusEffect);
}

void ASheriffAI::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, bool bShouldDealDamage, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::AddStatusEffect(ClassToCreateFrom, bShouldPerformTickAction, bShouldDealDamage, LifeTime, DamageToDeal, TickRate, CharacterThatInflictedStatusEffect);
}

AWeapon* ASheriffAI::GetEquippedWeapon()
{
	return Super::GetEquippedWeapon();
}

bool ASheriffAI::bIsInRange()
{
	return Super::bIsInRange();
}

bool ASheriffAI::bIsInRange(float OveriddenDesiredRange)
{
	return Super::bIsInRange(OveriddenDesiredRange);
}

CharacterState::StatusEffect ASheriffAI::GetStatusEffect()
{
	return Super::GetStatusEffect();
}

bool ASheriffAI::GetbIsInHardCC()
{
	return Super::GetbIsInHardCC();
}

bool ASheriffAI::GetbIsInSoftCC()
{
	return Super::GetbIsInSoftCC();
}

void ASheriffAI::Destroyed()
{
	return Super::Destroyed();
}

SheriffState ASheriffAI::GetSheriffState()
{
	return CurrentState;
}

bool ASheriffAI::bIsSoftCC()
{
	return Super::bIsSoftCC();
}

bool ASheriffAI::bIsHardCC()
{
	return Super::bIsHardCC();
}

void ASheriffAI::Die()
{
	return Super::Die();
}

AWeapon* ASheriffAI::EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip)
{
	return Super::EquipNewWeapon(WeaponToEquip);
}

void ASheriffAI::Lasso()
{
	//CurrentlyEquippedWeapon = GetEquippedWeapon();
	//if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
	//{
	//	if (BlackboardComponent->GetValueAsObject(TEXT("Target")) != NULL)
	//	{
	//		if (ACharacterController* PlayerReference = Cast<ACharacterController>(BlackboardComponent->GetValueAsObject(TEXT("Target"))))
	//		{
	//			CurrentLocation = GetActorLocation();
	//			PlayerLocation = PlayerReference->GetActorLocation();
	//			DistanceToPlayer = FVector::Dist(CurrentLocation, PlayerLocation);

	//			//If the player gets pulled into the Sheriff's knife attack range, he will let go of the rope to swing his knife
	//			CushionSpace = KnifeAttackRange;

	//			if (DistanceToPlayer > CushionSpace)
	//			{
	//				LassoCableComponent->CableLength = LassoLength;
	//				LassoCableComponent->SetAttachEndTo(PlayerReference, GetMesh()->GetSocketBoneName("pelvis"));
	//				FVector PullDirecton = PullingVelocity * (PlayerReference->GetActorLocation() - GetActorLocation());
	//				PlayerReference->GetMovementComponent()->AddInputVector(PullDirecton);

	//				AddStatusEffect(UStatusEffect_SoftCrowdControl::StaticClass(), false, 2.f, 0.f, this);
	//			}

	//			if (DistanceToPlayer < CushionSpace)
	//			{
	//				LassoCableComponent->SetAttachEndTo(this, GetMesh()->GetSocketBoneName("hand_r"));
	//			}
	//		}
	//	}
	//}
}

void ASheriffAI::Shoot()
{
	CurrentlyEquippedWeapon->Fire();
}

void ASheriffAI::Casting()
{

}

void ASheriffAI::SwingKnife()
{
}

void ASheriffAI::SetSheriffState(SheriffState NewStateToEnter)
{
	CurrentState = NewStateToEnter;
}

bool ASheriffAI::bSafeAttackingDistance()
{
	if (bIsInRange(AttackRange) && !bIsFlee())
	{
		UE_LOG(LogTemp, Display, TEXT("WE ARE IN THE BEAM"));
		return bIsFleeing = true;
	}
	return bIsFleeing = false;
}

bool ASheriffAI::bIsFlee()
{
	if (bIsInRange(CushionSpace))
	{
		UE_LOG(LogTemp, Display, TEXT("WE ARE FLEE"));
		return true;
	}
	return false;
}

void ASheriffAI::Aim(ACharacterController* PlayerToAimAt)
{
	//FixedWeapo+Rotation();
	FVector Direction = PlayerToAimAt->GetActorLocation() - GetActorLocation();
	FRotator NewRollRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	SetActorRotation(NewRollRotation);
}

//void ABountyHunter::Attack()
//{
//	if (CurrentlyEquippedWeapon != NULL)
//	{
//		if (CurrentlyEquippedWeapon->CanFire())
//		{
//			FixWeaponRotation();
//		}
//	}
//}

//void ASheriffAI::FixWeaponRotation()
//{
//	if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
//	{
//		if (BlackboardComponent->GetValueAsObject(TEXT("Target")) != NULL)
//		{
//			if (ACharacterController* RecastTarget = Cast<ACharacterController>(BlackboardComponent->GetValueAsObject(TEXT("Target"))))
//			{
//				if (CurrentlyEquippedWeapon != NULL)
//				{
//					FRotator DesiredWeaponRotation = GetActorRotation();
//					FVector DirectionToTarget = RecastTarget->GetActorLocation() - GetActorLocation();
//					if (DirectionToTarget.Size() > 300.f)
//					{
//						FRotator YawRotation = (RecastTarget->GetActorLocation() - CurrentlyEquippedWeapon->GetActorLocation()).Rotation();
//						DesiredWeaponRotation.Yaw = YawRotation.Yaw;
//					}
//					else
//					{
//						FRotator YawRotation = (GetActorLocation() + (GetMesh()->GetRightVector() * 256.f) - CurrentlyEquippedWeapon->GetActorLocation()).Rotation();
//
//						DesiredWeaponRotation.Yaw = YawRotation.Yaw;
//					}
//					FRotator RotationInDirection = FRotationMatrix::MakeFromX(DirectionToTarget).Rotator();
//					DesiredWeaponRotation.Pitch = RotationInDirection.Pitch;
//
//					CurrentlyEquippedWeapon->SetActorRotation(FMath::RInterpTo(CurrentlyEquippedWeapon->GetActorRotation(), DesiredWeaponRotation, GetWorld()->GetDeltaSeconds(), 200.f));
//				}
//			}
//		}
//	}
//}

//void ASherifAI::Flee(ACharacterController* PlayerToFleeFrom)
//{
//	FVector CurrentLocation = GetActorLocation();
//	FVector PlayerLocation = PlayerToFleeFrom->GetActorLocation();
//	FRotator RotationToPlayer = PlayerToFleeFrom->GetActorRotation();
//	FVector Direction = CurrentLocation - PlayerLocation;
//	FRotator DirectionRotation = Direction.Rotation();
//	FRotator NewRotation = -DirectionRotation;
//	float DistanceToPlayer = FVector::Dist(CurrentLocation, PlayerLocation);
//	SetActorRotation(NewRotation);
//	GetMovementComponent()->AddInputVector(DistanceToPlayer * Direction);
//
//	if (DistanceToPlayer > CushionSpace)
//	{
//		bIsFleeing = false;
//	}
//}