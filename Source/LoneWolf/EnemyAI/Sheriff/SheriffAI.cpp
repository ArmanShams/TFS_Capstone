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

	ConstructorHelpers::FClassFinder<AWeapon>RevolverAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/Sheriff/SheriffShotgunBP.SheriffShotgunBP_C'"));
	if (RevolverAsset.Class)
	{
		RevolverWeapon = (UClass*)RevolverAsset.Class;
	}

	ConstructorHelpers::FClassFinder<AActor>LassoAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/LassoBP.LassoBP_C'"));
	if (LassoAsset.Class)
	{
		UE_LOG(LogTemp, Display, TEXT("We have found the lasso!"));
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
}

void ASheriffAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	// Update the blackboard component keys
	//if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
	//{
	//	BlackboardComponent->SetValueAsBool(TEXT("bIsSoftCC"), bIsInSoftCC);
	//	BlackboardComponent->SetValueAsBool(TEXT("bIsInKnifeRange"), bIsInRange(KnifeAttackRange));
	//	BlackboardComponent->SetValueAsBool(TEXT("bIsInRevolverRange"), bIsInRange(RevolverAttackRange));
	//	BlackboardComponent->SetValueAsBool(TEXT("bIsInLassoRange"), bIsInRange(LassoAttackRange));
	//	BlackboardComponent->SetValueAsEnum(TEXT("CurrentState"), (uint8)CurrentState);
	//}

	// Use functions for the appropriate state
	switch (CurrentState)
	{
	case SheriffState::IDLE:
		break;
	case SheriffState::MELEE:
		UE_LOG(LogTemp, Display, TEXT("SHERIFFSTATE::MELEE"));
		if (bIsInRange(KnifeAttackRange))
		{
			CurrentlyEquippedWeapon = GetEquippedWeapon();
			if (CurrentlyEquippedWeapon->GetClass() != KnifeWeapon)
			{
				CurrentlyEquippedWeapon = EquipNewWeapon(KnifeWeapon);
			}
			//CurrentlyEquippedWeapon->Fire();
		}
		break;
	case SheriffState::RANGED:
		UE_LOG(LogTemp, Display, TEXT("SHERIFFSTATE::RANGED"));
		if (bIsInRange(RevolverAttackRange))
		{
			CurrentlyEquippedWeapon = GetEquippedWeapon();
			if (CurrentlyEquippedWeapon->GetClass() != KnifeWeapon)
			{
			EquipNewWeapon(RevolverWeapon);
			}
			//CurrentlyEquippedWeapon->Fire();
		}
		break;
	case SheriffState::CASTING:
		UE_LOG(LogTemp, Display, TEXT("SHERIFFSTATE::CASTING"));
		if (bIsInRange(LassoAttackRange))
		{
			CurrentlyEquippedWeapon = GetEquippedWeapon();
			if (CurrentlyEquippedWeapon->GetClass() != KnifeWeapon)
			{ 
				EquipNewWeapon(LassoWeapon);
			}
			//CurrentlyEquippedWeapon->Fire();
		}
		break;
	case SheriffState::LASSO:

		//if (bIsInRange(LassoAttackRange))
		//{
		//}
		break;
	default:
		break;
	}
	//if (bIsInRange())
	//{
	//	if (bIsInRange(LassoAttackRange))
	//	{
	//		Lasso();
	//	}
	//}
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
	SetSheriffState(SheriffState::MELEE);
	UE_LOG(LogTemp, Display, TEXT("Sheriff is trying to swing his knife"));
	if (DefaultWeapon = KnifeWeapon)
	{
		UE_LOG(LogTemp, Display, TEXT("Sheriff is swinging his knife"));
		// CurrentlyEquippedWeapon->Fire();
	}
}

void ASheriffAI::Shoot()
{
	SetSheriffState(SheriffState::RANGED);
	UE_LOG(LogTemp, Display, TEXT("Sheriff is trying to shoot"));
	if (DefaultWeapon = RevolverWeapon)
	{
		UE_LOG(LogTemp, Display, TEXT("Sheriff is shooting his shotgun"));
		// CurrentlyEquippedWeapon->Fire();
	}
}

void ASheriffAI::Casting()
{
	SetSheriffState(SheriffState::CASTING);
	UE_LOG(LogTemp, Display, TEXT("Sheriff is trying to cast lasso"));
	if (DefaultWeapon = LassoWeapon)
	{
		UE_LOG(LogTemp, Display, TEXT("Sheriff is readying the lasso ability"));
	}
}

void ASheriffAI::Lasso()
{
	SetSheriffState(SheriffState::LASSO);
	UE_LOG(LogTemp, Display, TEXT("Sheriff is trying to use lasso"));

	CurrentlyEquippedWeapon = GetEquippedWeapon();
	//if (CurrentlyEquippedWeapon->GetClass() != LassoWeapon)
	//{
	//	UE_LOG(LogTemp, Display, TEXT("Sheriff is using the lasso ability"));
	//	EquipNewWeapon(LassoWeapon);
	//}
		
	//if (DefaultWeapon = LassoWeapon)
	//{
	if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
	{
		if (BlackboardComponent->GetValueAsObject(TEXT("Target")) != NULL)
		{
			if (ACharacterController* PlayerReference = Cast<ACharacterController>(BlackboardComponent->GetValueAsObject(TEXT("Target"))))
			{
				// UE_LOG(LogTemp, Display, TEXT("Sheriff tried to lasso the player"));

				CurrentLocation = GetActorLocation();
				PlayerLocation = PlayerReference->GetActorLocation();
				DistanceToPlayer = FVector::Dist(CurrentLocation, PlayerLocation);

				//If the player gets pulled into the Sheriff's knife attack range, he will let go of the rope to swing his knife
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
					LassoCableComponent->SetAttachEndTo(this, GetMesh()->GetSocketBoneName("hand_r"));
				}
			}
		}
	}

}

AWeapon* ASheriffAI::EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip)
{
	CurrentlyEquippedWeapon = Super::EquipNewWeapon(WeaponToEquip);
	CurrentlyEquippedWeapon->SetActorRelativeRotation(FRotator(90.0f, -90.f, 90.f));
	CurrentlyEquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("hand_r"));
	return CurrentlyEquippedWeapon;
}