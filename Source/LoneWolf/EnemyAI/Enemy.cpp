// Fill out your copyright notice in the Description page of Project Settings.
// this is the enemy base class which will derive the enemys health, attacks, and status effects.

#include "LoneWolf.h"
#include "Enemy.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BrainComponent.h"
#include "Character/PlayerCharacter/CharacterController.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Health = MAXHEALTH;

	MoveSpeed = .04f;

	TurnRate = 0.25f;

	MaxRange = 100.0f;

	AttackFrequency = 5.f;

	AttackRange = 150.0f;

	DespawnTimer = 2.2f;

	ConstructorHelpers::FClassFinder<AWeapon>WeaponAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/KnifeBP_Arman.KnifeBP_Arman_C'"));

	if (WeaponAsset.Class)
	{
		//UE_LOG(LogTemp, Display, TEXT("WE HAVE FOUND THE CLASS"));
		DefaultWeapon = (UClass*)WeaponAsset.Class;
	}
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	//EnemyState = EState::Idle;

	//TimeSinceLastAttack = 0.0f;
	//Skill1Cooldown = MAX_FLT;
	//Skill2Cooldown = MAX_FLT;
	
	//EquipNewWeapon(DefaultWeapon);

	if (CurrentlyEquippedWeapon != NULL)
	{
		UE_LOG(LogTemp, Display, TEXT("Knife Equipped"));
	}
}

float AEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	float NewHealth = Health;
	
	NewHealth -= DamageAmount;

	if (NewHealth > MAXHEALTH)
	{
		NewHealth = MAXHEALTH;
	}

	UE_LOG(LogTemp, Display, TEXT("Enemy health modified, health was %f, now: %f"), Health, NewHealth);

	Health = NewHealth;

	if (ACharacterController* player = Cast<ACharacterController>(DamageCauser))
	{
		//UE_LOG(LogTemp, Display, TEXT("We are in the beam."));
		float RageGeneratedFromDamage = DamageAmount * 1.8f;

		player->AddRage(RageGeneratedFromDamage);

		if (NewHealth <= 0.f)
		{
			player->AddRage(RageGeneratedFromDamage * 2.0f);
		}
	}

	if (NewHealth <= 0.f)
	{
		Die();
		if (AAIController* AIController = Cast<AAIController>(GetController()))
		{
			if (UBrainComponent* BrainComponent = AIController->GetBrainComponent())
			{
				BrainComponent->StopLogic(FString("An enemy died, stopping logic."));
				GetCapsuleComponent()->SetCollisionProfileName(FName("NoCollision"));
			}
		}
	}

	return Health;
}

void AEnemy::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::AddStatusEffect(ClassToCreateFrom, bShouldPerformTickAction, LifeTime, TickRate, CharacterThatInflictedStatusEffect);
}


void AEnemy::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, bool bShouldDealDamage, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::AddStatusEffect(ClassToCreateFrom, bShouldPerformTickAction, bShouldDealDamage, LifeTime, DamageToDeal, TickRate, CharacterThatInflictedStatusEffect);

}

bool AEnemy::GetbIsInHardCC()
{
	return Super::GetbIsInHardCC();
}

bool AEnemy::GetbIsInSoftCC()
{
	return Super::GetbIsInSoftCC();
}

AWeapon* AEnemy::GetEquippedWeapon()
{
	return Super::GetEquippedWeapon();
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeSinceLastAttack += DeltaTime;

	//Skill1Cooldown += DeltaTime;
	//Skill2Cooldown += DeltaTime;

	//bIsAttacking();

}

void AEnemy::SetupPlayerInputComponent(class UInputComponent* InInputComponent)
{
	Super::SetupPlayerInputComponent(InInputComponent);
}

// Returns true if the distance between the Enemy and it's Target is less than AttackRange
// Uses the enemies default AttackRange
bool AEnemy::bIsInRange()
{
	return bIsInRange(AttackRange);
}
// Returns true if the distance between the Enemy and it's Target is less than the specified OveriddenDesiredRange
bool AEnemy::bIsInRange(float OveriddenDesiredRange)
{
	float DesiredRange = OveriddenDesiredRange;

	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		if (UBrainComponent* BrainComponent = AIController->GetBrainComponent())
		{
			if (UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent())
			{
				ACharacterController* CurrentTarget = Cast<ACharacterController>(BlackboardComponent->GetValue<UBlackboardKeyType_Object>(TEXT("Target")));

				if (CurrentTarget)
				{
					const FVector CurrentTargetLocation = CurrentTarget->GetActorLocation();
					const FVector MyLocation = GetActorLocation();
					const float CurrentDistance = FVector::Dist(CurrentTargetLocation, MyLocation);
 
					//UE_LOG(LogTemp, Warning, TEXT("MyLocation is %s"), *MyLocation.ToString());
					//UE_LOG(LogTemp, Warning, TEXT("CurrentDistance is %f"), CurrentDistance);
					return CurrentDistance < DesiredRange;

				}
			}
		}
	}

	return false;
}

bool AEnemy::bIsSoftCC()
{
	return Super::bIsSoftCC();
	//switch (Effects)
	//{
	//case CharacterState::SNARE:
	//	return true;
	//	break;

	//default:
	//	return false;
	//	break;
	//}
}

bool AEnemy::bIsHardCC()
{
	return Super::bIsHardCC();
	//switch (Effects)
	//{
	//case CharacterState::STUN:
	//	return true;
	//	break;

	//case CharacterState::KNOCKDOWN:
	//	return true;
	//	break;

	//default:
	//	return false;
	//	break;
	//}
}

void AEnemy::Die()
{
	Super::Die();
	if (CurrentlyEquippedWeapon != NULL)
	{
		CurrentlyEquippedWeapon->SetLifeSpan(DespawnTimer);
	}
	SetLifeSpan(DespawnTimer);
}

void AEnemy::Destroyed()
{
	Super::Destroyed();
}

CharacterState::StatusEffect AEnemy::GetStatusEffect()
{
	return Effects;
}

AWeapon* AEnemy::EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip)
{
	return CurrentlyEquippedWeapon = Super::EquipNewWeapon(WeaponToEquip);
}

//void AEnemy::EquipWeapon(TSubclassOf<AWeapon> WeaponToEquip)
//{
//	CurrentlyEquippedWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponToEquip);
//	CurrentlyEquippedWeapon->SetActorRelativeRotation(FRotator(25.f, -90.f, 90.f));
//	CurrentlyEquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("WeaponSocket"));
//	CurrentlyEquippedWeapon->SetOwner(this);
//}

void AEnemy::SetStatusEffect(CharacterState::StatusEffect NewStatusEffect)
{
	Effects = NewStatusEffect;
}









