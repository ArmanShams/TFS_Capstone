// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BrainComponent.h"
#include "Weapons/Weapon_Ranged.h"
#include "Character/CharacterController.h"
#include "RangedAI.h"


ARangedAI::ARangedAI()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	RootComponent = GetCapsuleComponent();
	GetMesh()->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Health = MAXHEALTH;
	
	ConstructorHelpers::FClassFinder<AWeapon>WeaponAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/Weapon_RifleBP.Weapon_RifleBP_C'"));
	if (WeaponAsset.Class)
	{
		DefaultWeaponClass = (UClass*)WeaponAsset.Class;
	}
}

float ARangedAI::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float NewHealth = Health;
	NewHealth -= DamageAmount;

	if (NewHealth > MAXHEALTH)
	{
		NewHealth = MAXHEALTH;
	}

	// UE_LOG(LogTemp, Display, TEXT("health modified, health is now: %f"), Health);

	Health = NewHealth;

	if (NewHealth <= 0.f)
	{
		CurrentlyEquippedWeapon->SetLifeSpan(0.1f);
		SetLifeSpan(0.1f);
	}

	return Health;
}

void ARangedAI::BeginPlay()
{
	Super::BeginPlay();

	if (DefaultWeaponClass != NULL)
	{
		// UE_LOG(LogTemp, Display, TEXT("Enemy Equipped Rifle"));
		CurrentlyEquippedWeapon = GetWorld()->SpawnActor<AWeapon>(DefaultWeaponClass);
		CurrentlyEquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("RightHand"));
		CurrentlyEquippedWeapon->SetActorRelativeRotation(FRotator(0.f, 270.f, 90.f));
	}
}

void ARangedAI::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	bPlayerDistance();

}

bool ARangedAI::bPlayerDistance()
{
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
	ACharacterController* Target = Cast<ACharacterController>(UGameplayStatics::GetPlayerCharacter(this, 0));
		if (Target)
		{
			const FVector PlayerLocation = Target->GetActorLocation();
			const FVector EnemyLocation = GetActorLocation();
			const float CurrentDistance = FVector::Dist(PlayerLocation, EnemyLocation);
			// UE_LOG(LogTemp, Warning, TEXT("CurrentDistance is %f"), CurrentDistance);
			if (CurrentDistance < AttackRange)
			{
				// UE_LOG(LogTemp, Warning, TEXT("You're in the enemy's range is %f"), CurrentDistance);
				CurrentlyEquippedWeapon->Fire();
				Aim();
			}
			return CurrentDistance < AttackRange;
		}
	}
	return false;
}

bool ARangedAI::Aim()
{
	return true;
}