// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "SheriffAnimInstance.h"
#include "SheriffAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Character/PlayerCharacter/CharacterController.h"
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
	AttackRange = 250.0f;
	// bCanMelee = false;

	ConstructorHelpers::FClassFinder<AWeapon>KnifeAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/KnifeBP_Arman.KnifeBP_Arman_C'"));
	if (KnifeAsset.Class)
	{
		DefaultWeapon = (UClass*)KnifeAsset.Class;
	}
}

void ASheriffAI::BeginPlay()
{
	Super::BeginPlay();
	CurrentState = SheriffState::IDLE;
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

	//switch (CurrentState)
	//{
	//	case SheriffState::IDLE:
	//	{
	//		DefaultWeapon = NULL;
	//	}
	//	break;

	//	case SheriffState::MELEE:
	//	{
	//		ConstructorHelpers::FClassFinder<AWeapon>KnifeAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/KnifeBP_Arman.KnifeBP_Arman_C'"));
	//		if (KnifeAsset.Class)
	//		{
	//			DefaultWeapon = (UClass*)KnifeAsset.Class;
	//		}	
	//	}
	//	break;

	//	case SheriffState::RANGED:
	//	{
	//		ConstructorHelpers::FClassFinder<AWeapon>KnifeAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/KnifeBP_Arman.KnifeBP_Arman_C'"));
	//		if (KnifeAsset.Class)
	//		{
	//			DefaultWeapon = (UClass*)KnifeAsset.Class;

	//		}
	//	}
	//	break;
	//	case SheriffState::LASSO
	//	{
	//		ConstructorHelpers::FClassFinder<AWeapon>LassoAsset(TEXT("Blueprint'/Game/Blueprints/Enemies/Sheriff/RopeBP.RopeBP_C'"));
	//		if (LassoAsset.Class)
	//		{
	//			DefaultWeapon = (UClass*)LassoAsset.Class;
	//		}
	//	}

	if (bIsInRange())
	{
		UE_LOG(LogTemp, Display, TEXT("You are in range of the Sheriff"));
		if (CurrentlyEquippedWeapon != NULL)
		{
			CurrentlyEquippedWeapon->Fire();
			
			// Lasso();
			/*if (bCanMelee == true)
			{
				CurrentlyEquippedWeapon->Fire();
			}
			if (bCanMelee = false)
			{
				CurrentlyEquippedWeapon->Fire();
			}*/
		}
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

//bool ASheriffAI::bCanLasso()
//{
//	return true;
//}

void ASheriffAI::Lasso(ACharacterController* Player, FHitResult& SweepHitResult)
{
	//if (Player = Cast<ACharacterController>(Cast<AAIController>(GetController()->GetBrainComponent()->GetBlackBoardComponent()->GetValueAsObject(TEXT("Target"))))
	//{
	//	FRotator CurrentRotation = GetActorRotation();
	FVector CurrentLocation = RootComponent->GetComponentLocation();
	FVector CurrentTargetLocation = Player->GetActorLocation();
	float SpeedOfLerp = 1.0f;

	FVector Difference = FMath::Lerp(CurrentLocation, CurrentTargetLocation, SpeedOfLerp);

	
	// UE_LOG(LogTemp, Display, TEXT("Lerp Difference: %s"), Difference.ToString());
	// Difference.Rotation();		// Get Rotation of Lerp

	//	FVector Difference = FVector(CurrentTargetLocation.X - CurrentLocation.X, CurrentTargetLocation.Y - CurrentLocation.Y, 0.f);

	//	SetActorRotation(FMath::Lerp(CurrentRotation, FRotator(0.f, Difference.Rotation().Yaw, 0.f), 0.2f));
	//	SetActorLocation(CurrentLocation.Z - 100.f, CurrentLocation.X - 50.f);
	//}
}

//void ASheriffAI::UpdateLassoTelegraph()
//{
//	if (LassoDecalActor != NULL)
//	{
//		if (UBlackboardComponent* BlackboardComponent = Cast<ASheriffAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
//		{ 
//		UE_LOG(LogTemp, Display, TEXT("Telegraph for Lasso displaying!"));
//		FRotator CurrentRotation = LassoDecalActor->GetActorRotation();
//		FVector CurrentLocation = GetActorLocation();
//		FVector CurrentTargetLocation = Cast<ACharacter>(BlackboardComponent->GetValue<UBlackboardKeyType_Object>(TEXT("Target")))->GetRootComponent()->GetComponentLocation();
//		FVector Difference = FVector(CurrentTargetLocation.X - CurrentLocation.X, CurrentTargetLocation.Y - CurrentLocation.Y, CurrentTargetLocation.Z - CurrentLocation.Z);
//
//		LassoDecalActor->SetActorRotation(FMath::Lerp(CurrentRotation, FRotator(CurrentRotation.Pitch, Difference.Rotation().Yaw, CurrentRotation.Roll), 0.1f));
//		}
//	}
//}
//
//void ASheriffAI::DisplayLassoTelegraph()
//{
//	LassoDecalActor = GetWorld()->SpawnActor<AActor>(LassoDecalClass);
//	LassoDecalActor->SetOwner(this);
//}

AWeapon* ASheriffAI::EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip)
{
	CurrentlyEquippedWeapon = Super::EquipNewWeapon(WeaponToEquip);
	CurrentlyEquippedWeapon->SetActorRelativeRotation(FRotator(90.0f, -90.f, 90.f));
	CurrentlyEquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("RightHand"));
	return CurrentlyEquippedWeapon;
}