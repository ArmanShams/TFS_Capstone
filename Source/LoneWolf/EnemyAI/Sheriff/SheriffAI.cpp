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

		//Check for status
		BlackboardComponent->SetValueAsEnum(TEXT("StatusEffects"), Effects);
		BlackboardComponent->SetValueAsEnum(TEXT("CurrentState"), (uint8)CurrentState);

		if (BlackboardComponent->GetValueAsObject(TEXT("Target")) != NULL)
		{
			switch (CurrentState)
			{
			case SheriffState::IDLE:
				break;
			case SheriffState::ATTACKING:
				Shoot();
				break;
			case SheriffState::CASTING:
				Casting();
				break;
			case SheriffState::LASSO:
				Lasso();
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

void ASheriffAI::SetSheriffState(SheriffState NewStateToEnter)
{
	CurrentState = NewStateToEnter;
}

void ASheriffAI::Aim(ACharacterController* PlayerToAimAt)
{
	//FixedWeapo+Rotation();
	FVector Direction = PlayerToAimAt->GetActorLocation() - GetActorLocation();
	FRotator NewRollRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	SetActorRotation(NewRollRotation);
}

void ASheriffAI::Shoot()
{
	CurrentlyEquippedWeapon->Fire();
}

void ASheriffAI::Casting()
{
	UE_LOG(LogTemp, Display, TEXT("Attempting to cast lasso in C++ class"));
}

void ASheriffAI::Lasso()
{
	UE_LOG(LogTemp, Display, TEXT("Completed Lasso task in C++ class"));
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