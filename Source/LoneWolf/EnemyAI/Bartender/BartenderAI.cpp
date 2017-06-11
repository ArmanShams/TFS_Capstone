// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BartenderAI.h"
#include "Weapons/Projectile.h"
#include "Weapons/Molotov.h"
#include "Weapons/BartenderKeg.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BrainComponent.h"
#include "AIController.h"

ABartenderAI::ABartenderAI()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Health = MAXHEALTH;

	MoveSpeed = .04f;

	TurnRate = 0.25f;

	MaxRange = 100.0f;

	AttackFrequency = 5.f;

	AttackRange = 250.0f;

	TimeForMolotovToReachTargetLocation = 4.0f;

	bIsAttacking = false;

	CushionSpace = 200.f;
}

void ABartenderAI::BeginPlay()
{
	Super::BeginPlay();
}

void ABartenderAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
	{

		BlackboardComponent->SetValueAsBool(TEXT("bIsInFleeRange"), bFlee);
		BlackboardComponent->SetValueAsBool(TEXT("bIsInAttackRange"), bAttack);
		BlackboardComponent->SetValueAsBool(TEXT("bIsAttacking"), bIsAttacking);

		bIsInRange(AttackRange);
	}

	TimeSinceLastAttack += DeltaSeconds;

	if (bIsAttacking)
	{
		//UE_LOG(LogTemp, Display, TEXT("JAM"));
	}
	else
	{
		//UE_LOG(LogTemp, Display, TEXT("NOJAM"));
	}


	if (TimeSinceLastAttack >= AttackFrequency)
	{
		if (bIsInRange())
		{

		}
	}
}

void ABartenderAI::SetupPlayerInputComponent(class UInputComponent* InInputComponent)
{
	Super::SetupPlayerInputComponent(InInputComponent);
}

void ABartenderAI::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::AddStatusEffect(ClassToCreateFrom, bShouldPerformTickAction, LifeTime, TickRate, CharacterThatInflictedStatusEffect);
}

void ABartenderAI::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, bool bShouldDealDamage, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::AddStatusEffect(ClassToCreateFrom, bShouldPerformTickAction, bShouldDealDamage, LifeTime, DamageToDeal, TickRate, CharacterThatInflictedStatusEffect);
}

float ABartenderAI::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

bool ABartenderAI::bIsInRange()
{
	return Super::bIsInRange(AttackRange);
}

bool ABartenderAI::bIsInRange(float OveriddenDesiredRange)
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter != NULL)
	{
		float DesiredRange = OveriddenDesiredRange;
		FVector EnemyLocation = GetActorLocation();
		FVector TargetLocation = PlayerCharacter->GetActorLocation();
		const float CurrentDistance = FVector::Dist(TargetLocation, EnemyLocation);

		if (CurrentDistance > CushionSpace && CurrentDistance <= AttackRange)
		{
			bAttack = true;
			bFlee = false;
		}

		if (CurrentDistance < CushionSpace)
		{
			bAttack = false;
			bFlee = true;
		}

		if (CurrentDistance > AttackRange)
		{
			bFlee = false;
			bAttack = false;
		}
	}
	return Super::bIsInRange(OveriddenDesiredRange);
}

AWeapon* ABartenderAI::GetEquippedWeapon()
{
	return Super::GetEquippedWeapon();
}

bool ABartenderAI::bIsSoftCC()
{
	return Super::bIsSoftCC();
}

bool ABartenderAI::bIsHardCC()
{
	return Super::bIsHardCC();
}

CharacterState::StatusEffect ABartenderAI::GetStatusEffect()
{
	return Super::GetStatusEffect();
}

void ABartenderAI::Destroyed()
{
	Super::Destroyed();
}

void ABartenderAI::Die()
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

AWeapon* ABartenderAI::EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip)
{
	CurrentlyEquippedWeapon = Super::EquipNewWeapon(WeaponToEquip);
	return CurrentlyEquippedWeapon;
}

void ABartenderAI::ThrowMolotov()
{
	if (AActor* ValidTarget = Cast<AActor>(Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent()->GetValueAsObject(TEXT("Target"))))
	{
		UClass* MolotovClass = LoadObject<UClass>(NULL, TEXT("Blueprint'/Game/Blueprints/Enemies/BartenderAI/MolotovBP.MolotovBP_C'"));
		if (MolotovClass)
		{
			TSubclassOf<AMolotov> SubClassOfMolotov = MolotovClass;

			AMolotov* SpawnedMolotov = GetWorld()->SpawnActor<AMolotov>(SubClassOfMolotov);
			SpawnedMolotov->SetActorLocation(GetActorLocation() + FVector(0.f, 0.f, 200.f));
			SpawnedMolotov->SetOwner(this);
			FVector TargetDestination = ValidTarget->GetActorLocation();
			//if (APawn* RecastTarget = Cast<APawn>(ValidTarget))
			//{
			//	if (RecastTarget->GetLastMovementInputVector() != FVector::ZeroVector)
			//	{
			//		TargetDestination += RecastTarget->GetVelocity();
			//	}
			//}
			SpawnedMolotov->SetMolotovVelocity(HitTargetLocationAtTime(SpawnedMolotov->GetActorLocation(), TargetDestination, FVector(0.f, 0.f, GetWorld()->GetGravityZ()), TimeForMolotovToReachTargetLocation));
			TimeSinceLastAttack = 0.f;
			UE_LOG(LogTemp, Display, TEXT("Time of launching Molotov: %f"), GetWorld()->GetTimeSeconds());
			//DrawDebugLine(GetWorld(), HitTargetLocationAtTime(T->GetActorLocation(), GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), FVector(0.f, 0.f, GetWorld()->GetGravityZ()), 2.0f), 5.f, FColor(255, 0, 0), true, 8);
		}
	}
}

void ABartenderAI::RollKeg()
{
	if (AActor* ValidTarget = Cast<AActor>(Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent()->GetValueAsObject(TEXT("Target"))))
	{
		UClass* KegClass = LoadObject<UClass>(NULL, TEXT("Blueprint'/Game/Blueprints/Enemies/BartenderAI/BarrelBP.BarrelBP_C'"));
		if (KegClass)
		{
			TSubclassOf<ABartenderKeg> SubClassOfKeg = KegClass;

			ABartenderKeg* SpawnedKeg = GetWorld()->SpawnActor<ABartenderKeg>(SubClassOfKeg);
			//SpawnedKeg->SetActorLocation(GetActorLocation() + FVector(0.f, 0.f, 200.f));
			SpawnedKeg->SetOwner(this);
			FVector TargetDestination = ValidTarget->GetActorLocation();

			TimeSinceLastAttack = 0.f;
			UE_LOG(LogTemp, Display, TEXT("Time of launching Molotov: %f"), GetWorld()->GetTimeSeconds());
			//DrawDebugLine(GetWorld(), HitTargetLocationAtTime(T->GetActorLocation(), GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), FVector(0.f, 0.f, GetWorld()->GetGravityZ()), 2.0f), 5.f, FColor(255, 0, 0), true, 8);
		}
	}
}

bool ABartenderAI::GetIsAttacking()
{
	return bIsAttacking;
}

void ABartenderAI::SetIsAttacking(bool NewValue)
{
	bIsAttacking = NewValue;
}

FVector ABartenderAI::HitTargetLocationAtTime(FVector StartPosition, FVector TargetPosition, FVector GravityBase, float TimeToTarget)
{
	FVector AtoB = TargetPosition - StartPosition;
	FVector Horizontal = GetHorizontalVector(AtoB, GravityBase);
	float HorizontalDistance = Horizontal.Size();
	FVector Vertical = GetVerticalVector(AtoB, GravityBase);
	float VerticalDistance = Vertical.Size() * Sign(FVector::DotProduct(Vertical, -GravityBase));

	float HorizontalSpeed = HorizontalDistance / TimeToTarget;
	float VerticalSpeed = (VerticalDistance + ((0.5f * GravityBase.Size()) * (TimeToTarget * TimeToTarget))) / TimeToTarget;
	//if (Horizontal.Normalize() && GravityBase.Normalize())
	{
		FVector Launch = (Horizontal.GetSafeNormal() * HorizontalSpeed) - (GravityBase.GetSafeNormal() * VerticalSpeed);
		return Launch;
	}
	return FVector::ZeroVector;
}

FVector ABartenderAI::GetHorizontalVector(FVector Direction, FVector GravityBase)
{
	FVector Output;
	FVector Perpendicular = FVector::CrossProduct(Direction, GravityBase);
	Perpendicular = FVector::CrossProduct(GravityBase, Perpendicular);
	Output = Direction.ProjectOnTo(Perpendicular); //FVector::Pro(Direction, Perpendicular);
	return Output;
}

FVector ABartenderAI::GetVerticalVector(FVector Direction, FVector GravityBase)
{
	FVector Output;
	//output = FVector.Project(AtoB, gravityBase);
	Output = Direction.ProjectOnTo(GravityBase);
	return Output;
}

float ABartenderAI::Sign(float RetrieveSignOf)
{
	if (RetrieveSignOf < 0)
	{
		return -1.f;
	}
	if (RetrieveSignOf > 0)
	{
		return 1.0f;
	}
	return 0;
}

