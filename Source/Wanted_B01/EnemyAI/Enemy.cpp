// Fill out your copyright notice in the Description page of Project Settings.
// this is the enemy base class which will derive the enemys health, attacks, and status effects.

#include "Wanted_B01.h"
#include "Enemy.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BrainComponent.h"
#include "EnemyMelee.h"
#include "Character/CharacterController.h"
#include "Weapons/Weapon.h"


// Sets default values
AEnemy::AEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Health = MAXHEALTH;

	MoveSpeed = .04f;

	TurnRate = 0.25f;

	MaxRange = 100.0f;

	AttackFrequency = 5.f;

	isInRange = 5.0f;

	MeleeRange = 150.0f;


	ConstructorHelpers::FClassFinder<AWeapon>WeaponAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/KnifeBP.KnifeBP_C'"));

	if (WeaponAsset.Class)

	{

		UE_LOG(LogTemp, Display, TEXT("WE HAVE FOUND THE CLASS"));

		DefaultWeapon = (UClass*)WeaponAsset.Class;

	}
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	EnemyState = EState::Idle;

	LastAttacked = MAX_FLT;
	Skill1Cooldown = MAX_FLT;
	Skill2Cooldown = MAX_FLT;

	EquipKnife();

	if (CurrentlyEquippedWeapon != NULL)

	{

		UE_LOG(LogTemp, Display, TEXT("Knife Equipped"));

	}
}

float AEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float NewHealth = Health;
	NewHealth -= DamageAmount;

	if (NewHealth > MAXHEALTH)
	{
		NewHealth = MAXHEALTH;
	}

	UE_LOG(LogTemp, Display, TEXT("Player health modified, health is now: %f"), Health);

	Health = NewHealth;

	if (NewHealth <= 0.f)
	{
		CurrentlyEquippedWeapon->SetLifeSpan(0.1f);
		SetLifeSpan(0.1f);
	}

	return Health;
}



// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LastAttacked += DeltaTime;

	Skill1Cooldown += DeltaTime;
	Skill2Cooldown += DeltaTime;

	bIsAttacking();
	//if (bIsAttacking && LastAttacked >= AttackFrequency && isInRange)
	//{
	//	AttackType = FMath::RandRange(0, 2);

	//	Attack(AttackType);
	//}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}


void AEnemy::Enemy()
{
	//kills nothing, does nothing. 
	//if (isPhil == true)
	//{
	//philbertSuspended = PhilbertDoesStupid + ArmanFlipsShit;
	//}
}

bool AEnemy::bIsAttacking()
{
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{

		if (UBrainComponent* BrainComponent = AIController->GetBrainComponent())
		{
			if (UBlackboardComponent* BlackboardComponent = BrainComponent->GetBlackboardComponent()) 
			{
				ACharacterController* CurrentTarget = Cast<ACharacterController>(BlackboardComponent->GetValue<UBlackboardKeyType_Object>(TEXT("Target")));
			
			//if (!BrainComponent->GetBlackboardComponent())
			//{
			//	UE_LOG(LogTemp, Warning, TEXT("broken here"));
			//}

			//AActor* CurrentTarget = Cast<AActor>(BrainComponent->GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(TEXT("Target")));

				if (CurrentTarget)
				{
					const FVector CurrentTargetLocation = CurrentTarget->GetActorLocation();
					const FVector MyLocation = GetActorLocation();
					const float CurrentDistance = FVector::Dist(CurrentTargetLocation, MyLocation);
					//UE_LOG(LogTemp, Warning, TEXT("CurrentTargetLocation is %s"),  *CurrentTargetLocation.ToString());
					//UE_LOG(LogTemp, Warning, TEXT("MyLocation is %s"), *MyLocation.ToString());
					//UE_LOG(LogTemp, Warning, TEXT("CurrentDistance is %f"), CurrentDistance);
					return CurrentDistance < MeleeRange;
	
				}
			}
		}
	}

	return false;
}

void AEnemy::Attack(int32 AttackType)
{
	LastAttacked = 0.f;


	if (AttackType == 0)
	{
		//BasicAttack();
	}

	else if ((AttackType == 1) && (Skill1Cooldown >= 10.f))
	{
		//Skill1();
	}

	else if ((AttackType == 2) && (Skill2Cooldown >= 10.f))
	{
		//Skill2();
	}

	else
	{
		//BasicAttack();
	}

}

void AEnemy::BasicAttack(Effects effect, float Range)
{
	//bIsAttacking = true;

	//attack has effect application

	//range also gets applied for specific attack

}

void AEnemy::AttackEnd()
{
	//bIsAttacking = false;
}

void AEnemy::Skill1(Effects effect, float Range)
{
	//bIsAttacking = true;

	Skill1Cooldown = 0.f;
	//attack has effect application

	//range also gets applied for specific attack

}

void AEnemy::Skill2(Effects effect, float Range)
{
	//bIsAttacking = true;

	Skill2Cooldown = 0.f;
	//attack has effect application

	//range also gets applied for specific attack

}

void AEnemy::EquipKnife()
{

	CurrentlyEquippedWeapon = GetWorld()->SpawnActor<AWeapon>(DefaultWeapon);

	CurrentlyEquippedWeapon->SetActorRelativeRotation(FRotator(0.f, 0.f, 0.f));

	CurrentlyEquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("WeaponSocket"));


}








