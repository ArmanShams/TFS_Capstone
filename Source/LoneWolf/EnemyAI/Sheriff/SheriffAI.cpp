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

	FName LassoSocket = TEXT("RightHand");
	LassoCableComponent = CreateDefaultSubobject<UCableComponent>(TEXT("Cable Component"));
	LassoCableComponent->AttachTo(GetMesh(), LassoSocket);

	ConstructorHelpers::FClassFinder<AWeapon>KnifeAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/KnifeBP_Arman.KnifeBP_Arman_C'"));
	if (KnifeAsset.Class)
	{
		KnifeWeapon = (UClass*)KnifeAsset.Class;
	}

	ConstructorHelpers::FClassFinder<AWeapon>RevolverAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/SheriffRevolverBP.SheriffRevolverBP_C'"));
	if (RevolverAsset.Class)
	{
		RevolverWeapon = (UClass*)RevolverAsset.Class;
	}

	ConstructorHelpers::FClassFinder<AActor>LassoAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/LassoBP.LassoBP_C'"));
	if (LassoAsset.Class)
	{
		LassoWeapon = (UClass*)LassoAsset.Class;
	}

	DefaultWeapon = KnifeWeapon;
}

void ASheriffAI::BeginPlay()
{
	Super::BeginPlay();
	CurrentState = SheriffState::IDLE;
	DefaultWeapon = KnifeWeapon;
}

SheriffState ASheriffAI::GetSheriffState()
{
	return CurrentState;
}

void ASheriffAI::SetSheriffState(SheriffState NewStateToEnter)
{
	CurrentState = NewStateToEnter;
	UE_LOG(LogTemp, Display, TEXT("Altering the Sheriff's state"));
}

void ASheriffAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	// Update the blackboard component keys
	if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
	{
		BlackboardComponent->SetValueAsBool(TEXT("IsSoftCC"), bIsInSoftCC);
		BlackboardComponent->SetValueAsBool(TEXT("bCanSwingKnife"), bIsInRange(KnifeAttackRange));
		BlackboardComponent->SetValueAsBool(TEXT("bCanShootRevolver"), bIsInRange(RevolverAttackRange));
		BlackboardComponent->SetValueAsBool(TEXT("bCanLasso"), bIsInRange(LassoAttackRange));
		BlackboardComponent->SetValueAsEnum(TEXT("CurrentState"), (uint8)CurrentState);
	}

	// Use functions for the appropriate state
	switch (CurrentState)
	{
	case SheriffState::IDLE:
		break;
	case SheriffState::MELEE:
		if (bIsInRange(KnifeAttackRange))
		{	/* Swing Knife */	}
		break;
	case SheriffState::RANGED:
		if (bIsInRange(RevolverAttackRange))
		{	/* Shoot Revolver */	}
		break;
	case SheriffState::CASTING:
		if (bIsInRange(LassoAttackRange))
		{	/* Cast Lasso */	}
		break;
	case SheriffState::LASSO:
		if (bIsInRange(LassoAttackRange))
		{	/* Cast Lasso */	}
		break;
	default:
		break;
	}

	if (bIsInRange())
	{
		Lasso();
	}
	if (!bIsInRange())
	{
		LassoCableComponent->SetAttachEndTo(this, GetMesh()->GetSocketBoneName("RightHand"));
	}
}

void ASheriffAI::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

float ASheriffAI::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
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

bool ASheriffAI::bIsInRange(float OveriddenDesiredRange)
{
	return Super::bIsInRange(OveriddenDesiredRange);
}

bool ASheriffAI::bIsInRange()
{
	return Super::bIsInRange();
}

bool ASheriffAI::bIsSoftCC()
{
	return Super::bIsSoftCC();
}

bool ASheriffAI::bIsHardCC()
{
	return Super::bIsHardCC();
}

void ASheriffAI::Destroyed()
{
	Super::Destroyed();
}

void ASheriffAI::SwingKnife()
{
	if (DefaultWeapon = KnifeWeapon)
	{
		CurrentlyEquippedWeapon->Fire();
	}
}

void ASheriffAI::ShootRevolver()
{
	if (DefaultWeapon = RevolverWeapon)
	{
		CurrentlyEquippedWeapon->Fire();
	}
}

void ASheriffAI::Lasso()
{
	if (DefaultWeapon = LassoWeapon)
	{
		if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
		{
			if (BlackboardComponent->GetValueAsObject(TEXT("Target")) != NULL)
			{
				if (ACharacterController* PlayerReference = Cast<ACharacterController>(BlackboardComponent->GetValueAsObject(TEXT("Target"))))
				{
					UE_LOG(LogTemp, Display, TEXT("Sheriff tried to lasso the player"));

					CurrentLocation = GetActorLocation();
					PlayerLocation = PlayerReference->GetActorLocation();
					DistanceToPlayer = FVector::Dist(CurrentLocation, PlayerLocation);

					// If the player gets pulled into the Sheriff's knife attack range, he will let go of the rope to swing his knife
					CushionSpace = KnifeAttackRange;

					if (DistanceToPlayer > CushionSpace)
					{
						LassoCableComponent->CableLength = LassoLength;
						LassoCableComponent->SetAttachEndTo(PlayerReference, GetMesh()->GetSocketBoneName("pelvis"));
						FVector PullDirecton = PullingVelocity * (PlayerReference->GetActorLocation() - GetActorLocation());
						PlayerReference->GetMovementComponent()->AddInputVector(PullDirecton);

						AddStatusEffect(UStatusEffect_SoftCrowdControl::StaticClass(), false, 2.f, 0.f, this);

					}

					if (DistanceToPlayer < CushionSpace)
					{
						LassoCableComponent->SetAttachEndTo(this, GetMesh()->GetSocketBoneName("RightHand"));
					}
				}
			}
		}
	}
}

AWeapon* ASheriffAI::EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip)
{
	CurrentlyEquippedWeapon = Super::EquipNewWeapon(WeaponToEquip);
	CurrentlyEquippedWeapon->SetActorRelativeRotation(FRotator(90.0f, -90.f, 90.f));
	CurrentlyEquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("RightHand"));
	return CurrentlyEquippedWeapon;
}