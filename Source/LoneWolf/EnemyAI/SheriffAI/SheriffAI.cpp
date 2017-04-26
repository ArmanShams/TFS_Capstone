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
	AttackRange = 1000.0f;

	FName LassoSocket = TEXT("RightHand");
	LassoCableComponent = CreateDefaultSubobject<UCableComponent>(TEXT("Cable Component"));
	LassoCableComponent->AttachTo(GetMesh(), LassoSocket);

	ConstructorHelpers::FClassFinder<AWeapon>KnifeAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/KnifeBP_Arman.KnifeBP_Arman_C'"));
	if (KnifeAsset.Class)
	{
		DefaultWeapon = (UClass*)KnifeAsset.Class;
	}

	ConstructorHelpers::FClassFinder<AActor>LassoAsset(TEXT("Blueprint'/Game/Blueprints/Enemies/Sheriff/LassoBP.LassoBP_C'"));
	if (LassoAsset.Class)
	{
		UE_LOG(LogTemp, Display, TEXT("Lasso class found!"));
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

	FVector LinkDistance;
	LinkDistance.X = AttackRange;

	FVector LinkStart = GetActorLocation();
	FVector LinkEnd = LinkStart + LinkDistance;
	DrawDebugLine(GetWorld(), LinkStart, LinkEnd, FColor(255, 0, 0), false, -1.f, 0, 7.f);

	if (bIsInRange())
	{
		Lasso();

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


void ASheriffAI::Lasso()
{
	if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
	{
		if (BlackboardComponent->GetValueAsObject(TEXT("Target")) != NULL)
		{
			if (ACharacterController* PlayerReference = Cast<ACharacterController>(BlackboardComponent->GetValueAsObject(TEXT("Target"))))
			{
				UMeshComponent* PlayerMesh = PlayerReference->GetMesh();
				FVector LassoTarget = PlayerMesh->GetSocketLocation("pelvis");
			
				LassoCableComponent->SetAttachEndTo(PlayerReference,  RootComponent->GetDefaultSceneRootVariableName());
				LassoCableComponent->EndLocation = LassoTarget;
				LassoCableComponent->CableLength = 50;

				FVector CurrentLocation = GetActorLocation();
				FVector PullingVelocity;
				float ForceAmount = -0.1f;

				PullingVelocity.X = CurrentLocation.X * ForceAmount;
				PullingVelocity.Y = CurrentLocation.Y * ForceAmount;

				ALoneWolfCharacter* PlayerActor = PlayerReference;
				PlayerActor->LaunchCharacter(PullingVelocity, false, false);

				//PlayerReference->AddStatusEffect(UStatusEffect_SoftCrowdControl::StaticClass(), false, .5f, 0.f, Cast<ALoneWolfCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()));
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