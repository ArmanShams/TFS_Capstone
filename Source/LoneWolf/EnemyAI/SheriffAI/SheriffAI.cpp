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

	ConstructorHelpers::FClassFinder<AWeapon>SheriffWeaponAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/PlayerRevolverBlueprint.PlayerRevolverBlueprint_C'"));

	if (SheriffWeaponAsset.Class)
	{
		DefaultWeapon = (UClass*)SheriffWeaponAsset.Class;
	}

	ConstructorHelpers::FClassFinder<AActor>LassoDecalActor(TEXT("Texture2D'/Game/Blueprints/Enemies/Sheriff/Lasso_Visual_Telegraph.Lasso_Visual_Telegraph_C'"));
	if(LassoDecalActor.Class)
	{
		LassoDecalClass = (UClass*)LassoDecalActor.Class;
	}
}

void ASheriffAI::BeginPlay()
{
	Super::BeginPlay();
}

void ASheriffAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(bIsInRange())
	{
		if (CurrentlyEquippedWeapon != NULL)
		{
			CurrentlyEquippedWeapon->Fire();
		}
	}
	if (bIsInRange() && bCanLasso())
	{
		UpdateLassoTelegraph();
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

bool ASheriffAI::bCanLasso()
{
	return true;
}

void ASheriffAI::Lasso(ACharacterController* Player)
{
	if (Player)
	{
			FVector CurrentLocation = GetActorLocation();
			FVector CurrentTargetLocation = Player->GetRootComponent()->GetComponentLocation();
			
			 
	}
}

void ASheriffAI::UpdateLassoTelegraph()
{
	if (LassoDecalActor != NULL)
	{
		if (UBlackboardComponent* BlackboardComponent = Cast<ASheriffAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
		{ 
		UE_LOG(LogTemp, Display, TEXT("Telegraph for Lasso displaying!"));
		FRotator CurrentRotation = LassoDecalActor->GetActorRotation();
		FVector CurrentLocation = GetActorLocation();
		FVector CurrentTargetLocation = Cast<ACharacter>(BlackboardComponent->GetValue<UBlackboardKeyType_Object>(TEXT("Target")))->GetRootComponent()->GetComponentLocation();
		FVector Difference = FVector(CurrentTargetLocation.X - CurrentLocation.X, CurrentTargetLocation.Y - CurrentLocation.Y, CurrentTargetLocation.Z - CurrentLocation.Z);

		LassoDecalActor->SetActorRotation(FMath::Lerp(CurrentRotation, FRotator(CurrentRotation.Pitch, Difference.Rotation().Yaw, CurrentRotation.Roll), 0.1f));
		}
	}
}

void ASheriffAI::DisplayLassoTelegraph()
{
	LassoDecalActor = GetWorld()->SpawnActor<AActor>(LassoDecalClass);
	LassoDecalActor->SetOwner(this);
}

AWeapon* ASheriffAI::EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip)
{
	CurrentlyEquippedWeapon = Super::EquipNewWeapon(WeaponToEquip);
	CurrentlyEquippedWeapon->SetActorRelativeRotation(FRotator(90.0f, -90.f, 90.f));
	CurrentlyEquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("RightHand"));
	return CurrentlyEquippedWeapon;
}