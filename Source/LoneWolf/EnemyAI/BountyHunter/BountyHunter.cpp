// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "Environment/BearTrap.h"
#include "TrapLocations.h"
#include "BountyHunter.h"
#include "Engine.h"
#include "Weapons/Weapon.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BrainComponent.h"
#include "Character/PlayerCharacter/CharacterController.h"
#include "Character/StatusEffects/StatusEffect_HardCrowdControl.h"

ABountyHunter::ABountyHunter()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = GetCapsuleComponent();
	GetMesh()->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABountyHunter ::OnActorBeginOverlap);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	Health = MAXHEALTH;
	MoveSpeed = .01f;
	TurnRate = 0.25f;
	MaxRange = 300.0f;
	AttackFrequency = 1.f;
	AttackRange = 3000.0f;
	MaximumTrapsAllowed = 3;
	bPlayRecoilAnimation = false;
	CurrentState = BounterHunterState::IDLE;

	ConstructorHelpers::FClassFinder<AWeapon>WeaponAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/Weapon_RifleBP.Weapon_RifleBP_C'"));
	if (WeaponAsset.Class)
	{// UE_LOG(LogTemp, Display, TEXT("Found the rifle."));
		DefaultWeapon = (UClass*)WeaponAsset.Class;
	}

	ConstructorHelpers::FClassFinder<ABearTrap>TrapAsset(TEXT("Blueprint'/Game/Blueprints/Enemies/BountyHunterAI/BearTrapBP.BearTrapBP_C'"));
	if (TrapAsset.Class)
	{// UE_LOG(LogTemp, Display, TEXT("Found the trap."));
		BearTrapClass = (UClass*)TrapAsset.Class;
	}
}

void ABountyHunter::BeginPlay()
{
	Super::BeginPlay();
	EquipNewWeapon(DefaultWeapon);
}

void ABountyHunter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bPlayRecoilAnimation)
	{
		bPlayRecoilAnimation = false;
	}
	if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
	{
		BlackboardComponent->SetValueAsBool(TEXT("IsHardCC"), bIsInHardCC);
		BlackboardComponent->SetValueAsBool(TEXT("IsSoftCC"), bIsInSoftCC);
		BlackboardComponent->SetValueAsBool(TEXT("bCanAttackTarget"), bIsInRange());

		if (CurrentState == BounterHunterState::READYINGATTACK && CurrentlyEquippedWeapon != NULL)
		{
			if (BlackboardComponent->GetValueAsObject(TEXT("Target")) != NULL)
			{
				if (ACharacterController* RecastTarget = Cast<ACharacterController>(BlackboardComponent->GetValueAsObject(TEXT("Target"))))
				{
					FRotator DesiredWeaponRotation = GetActorRotation();

					FVector DirectionToTarget = RecastTarget->GetActorLocation() - GetActorLocation(); //FVector(RecastTarget->GetActorLocation().X - GetActorLocation().X, RecastTarget->GetActorLocation().Y - GetActorLocation().Y, RecastTarget->GetActorLocation().Z - GetActorLocation().Z);
					if (DirectionToTarget.Size() > 300.f)
					{
						FRotator YawRotation = (RecastTarget->GetActorLocation() - CurrentlyEquippedWeapon->GetActorLocation()).Rotation();
						DesiredWeaponRotation.Yaw = YawRotation.Yaw;
					}
					else
					{
						FRotator YawRotation = (GetActorLocation() + (GetMesh()->GetRightVector() * 256.f) - CurrentlyEquippedWeapon->GetActorLocation()).Rotation();
						//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetMesh()->GetRightVector() * 256.f, FColor(255, 255, 255), false, 0.018f, 8, 12.333f);
						DesiredWeaponRotation.Yaw = YawRotation.Yaw;
					}
					FRotator RotationInDirection = FRotationMatrix::MakeFromX(DirectionToTarget).Rotator();
					DesiredWeaponRotation.Pitch = RotationInDirection.Pitch;

					CurrentlyEquippedWeapon->SetActorRotation(FMath::RInterpTo(CurrentlyEquippedWeapon->GetActorRotation(), DesiredWeaponRotation, GetWorld()->GetDeltaSeconds(), 200.f));
				}
			}
		}
	}
}

float ABountyHunter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ABountyHunter::SetupPlayerInputComponent(class UInputComponent* InInputComponent)
{
	Super::SetupPlayerInputComponent(InInputComponent);
}

void ABountyHunter::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::AddStatusEffect(ClassToCreateFrom, bShouldPerformTickAction, LifeTime, TickRate, CharacterThatInflictedStatusEffect);
}

void ABountyHunter::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, bool bShouldDealDamage, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::AddStatusEffect(ClassToCreateFrom, bShouldPerformTickAction, bShouldDealDamage, LifeTime, DamageToDeal, TickRate, CharacterThatInflictedStatusEffect);
}

AWeapon* ABountyHunter::GetEquippedWeapon()
{
	return Super::GetEquippedWeapon();
}

bool ABountyHunter::bIsInRange()
{
	return Super::bIsInRange(AttackRange);
}

bool ABountyHunter::bIsInRange(float OveriddenDesiredRange)
{
	return Super::bIsInRange(OveriddenDesiredRange);
}

bool ABountyHunter::GetbIsInHardCC()
{
	return Super::GetbIsInHardCC();
}

bool ABountyHunter::GetbIsInSoftCC()
{
	return Super::GetbIsInSoftCC();
}

bool ABountyHunter::bIsSoftCC()
{
	return Super::bIsSoftCC();
}

bool ABountyHunter::bIsHardCC()
{
	return Super::bIsHardCC();
}

void ABountyHunter::Destroyed()
{
	Super::Destroyed();	// Any actors spawned by this that need to be destroyed/cleaned up should be done so here before Super::Destroyed() is called.
}


bool ABountyHunter::bCanTriggerRecoilAnimation()
{
	return bPlayRecoilAnimation;
}

void ABountyHunter::SetBountyHunterState(BounterHunterState NewState)
{
	CurrentState = NewState;
}

AWeapon* ABountyHunter::EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip)
{
	CurrentlyEquippedWeapon = Super::EquipNewWeapon(WeaponToEquip);
	CurrentlyEquippedWeapon->SetActorRelativeRotation(FRotator(30.f, -90.f, 90.f)); //CurrentlyEquippedWeapon->SetActorLocation(GetMesh()->GetSocketLocation(FName("hand_r")));
	return CurrentlyEquippedWeapon;
}

void ABountyHunter::SetBearTrap(ATrapLocations* NewTrapLocation, const FHitResult& SweepResult)
{
	if (!NewTrapLocation->bIsOccupied)
	{
		UE_LOG(LogTemp, Display, TEXT("The trap location is now occupied"));
		if (BearTrapClass != NULL)
		{
			if (TrapArray.Num() >= MaximumTrapsAllowed)
			{
				AActor* TrapToDelete = TrapArray.Pop();
				TrapToDelete->SetLifeSpan(0.1f);
				UE_LOG(LogTemp, Display, TEXT("Element popped from Trap Array"));
			}
			BearTrapPlaced = GetWorld()->SpawnActor<ABearTrap>(BearTrapClass);
			BearTrapPlaced->SetActorRelativeLocation(GetMesh()->GetSocketLocation("RightToe_End"));
			// BearTrapPlaced->SetLifeSpan(5.0f);
			BearTrapPlaced->SetOwner(this);
			BearTrapPlaced->SetLocationBeingOccupied(NewTrapLocation);
			TrapArray.Add(BearTrapPlaced);
			UE_LOG(LogTemp, Display, TEXT("Bounty Hunter set a bear trap, trap added to array list"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("The Trap Location is already occupied, the bounty hunter will not try to place a trap here"));
	}
}

void ABountyHunter::OnActorBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (ATrapLocations* RecastedOverlappingActor = Cast<ATrapLocations>(OtherActor))
	{
		SetBearTrap(RecastedOverlappingActor, SweepResult);
		RecastedOverlappingActor->bIsOccupied = true;
	}
}

void ABountyHunter::Attack()
{
	if (CurrentlyEquippedWeapon != NULL)
	{
		if (CurrentlyEquippedWeapon->CanFire())
		{
			CurrentState = BounterHunterState::READYINGATTACK;
			CurrentlyEquippedWeapon->Fire();
			bPlayRecoilAnimation = true;
		}
		/*
		if (CurrentlyEquippedWeapon->Fire())
		{
			bPlayRecoilAnimation = true;
		}
		else
		{
			bPlayRecoilAnimation = false;
		}
		*/
	}
}

void ABountyHunter::EquipWeapon(TSubclassOf<AWeapon> WeaponToEquip)
{

}