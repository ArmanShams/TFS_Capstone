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
	CushionSpace = 250.f;
	AttackRange = 500.0f;

	FName LassoSocket = TEXT("hand_r");
	LassoCableComponent = CreateDefaultSubobject<UCableComponent>(TEXT("Cable Component"));
	LassoCableComponent->AttachTo(GetMesh(), LassoSocket);
	//LassoCableComponent->AttachEndTo();

	ConstructorHelpers::FClassFinder<AWeapon>ShotgunAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/Sheriff/SheriffShotgunBP.SheriffShotgunBP_C'"));
	if (ShotgunAsset.Class)
	{
		DefaultWeapon = (UClass*)ShotgunAsset.Class;
	}

	ConstructorHelpers::FClassFinder<AActor>LassoAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/LassoBP.LassoBP_C'"));
	if (LassoAsset.Class)
	{
		UE_LOG(LogTemp, Display, TEXT("We have found the lasso!"));
		LassoWeapon = (UClass*)LassoAsset.Class;
	}
}

void ASheriffAI::BeginPlay()
{
	Super::BeginPlay();
	EquipNewWeapon(DefaultWeapon);
}

void ASheriffAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	

	if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
	{
		bIsInRange(AttackRange);

		//Animation																	Variables:
		BlackboardComponent->SetValueAsBool(TEXT("IsHardCC"), bIsInHardCC);			// bIsHardCC
		BlackboardComponent->SetValueAsBool(TEXT("IsSoftCC"), bIsInSoftCC);			// bIsSoftCC

		//Checking for the range
		BlackboardComponent->SetValueAsBool(TEXT("bIsInFleeRange"), bInFleeRange);
		BlackboardComponent->SetValueAsBool(TEXT("bIsInLassoRange"), bInLassoRange);
		BlackboardComponent->SetValueAsBool(TEXT("bIsInAttackRange"), bInAttackRange);

		//Check for status
		BlackboardComponent->SetValueAsEnum(TEXT("StatusEffects"), Effects);
		BlackboardComponent->SetValueAsEnum(TEXT("CurrentState"), (uint8)CurrentState);

		if (BlackboardComponent->GetValueAsObject(TEXT("Target")) != NULL)
		{
			switch (CurrentState)
			{
			case SheriffState::IDLE:
				break;
			case SheriffState::ATTACKING:
				Shoot();
				break;
			case SheriffState::CASTING:
				Casting();
				break;
			case SheriffState::LASSO:
				Lasso();
				break;
			case SheriffState::FLEEING:
				break;
			default:
				UE_LOG(LogTemp, Display, TEXT("There's been an error in setting the state of the Sheriff"));
				break;
			}
		}

		if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
		{
			if (BlackboardComponent->GetValueAsObject(TEXT("Target")) != NULL)
			{
				if (ACharacterController* RecastTarget = Cast<ACharacterController>(BlackboardComponent->GetValueAsObject(TEXT("Target"))))
				{
					if (CurrentlyEquippedWeapon != NULL)
					{
						FRotator DesiredWeaponRotation = GetActorRotation();
						FVector DirectionToTarget = RecastTarget->GetActorLocation() - GetActorLocation();
						if (DirectionToTarget.Size() > 300.f)
						{
							FRotator YawRotation = (RecastTarget->GetActorLocation() - CurrentlyEquippedWeapon->GetActorLocation()).Rotation();
							DesiredWeaponRotation.Yaw = YawRotation.Yaw;
						}
						else
						{
							FRotator YawRotation = (GetActorLocation() + (GetMesh()->GetRightVector() * 256.f) - CurrentlyEquippedWeapon->GetActorLocation()).Rotation();

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
}

float ASheriffAI::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ASheriffAI::SetupPlayerInputComponent(class UInputComponent* InInputComponent)
{
	Super::SetupPlayerInputComponent(InInputComponent);
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

bool ASheriffAI::bIsInRange()
{
	return Super::bIsInRange();
}

bool ASheriffAI::bIsInRange(float OveriddenDesiredRange)
{
	//return Super::bIsInRange(OveriddenDesiredRange);

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter != NULL)
	{
		float DesiredRange = OveriddenDesiredRange;
		FVector CurrentLocation = GetActorLocation();
		FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		const float CurrentDistance = FVector::Dist(PlayerLocation, CurrentLocation);

		if (CurrentDistance > CushionSpace && CurrentDistance <= AttackRange)
		{
			DrawDebugLine(GetWorld(), CurrentLocation, PlayerLocation, FColor::White, false, -1, 0, 12.333);
			bInAttackRange = true;
			bInFleeRange = false;
			bInLassoRange = false;
		}

		if (CurrentDistance < CushionSpace)
		{
			DrawDebugLine(GetWorld(), CurrentLocation, PlayerLocation, FColor::Red, false, -1, 0, 12.333);
			bInAttackRange = false;
			bInFleeRange = true;
			bInLassoRange = false;
		}

		if (CurrentDistance > AttackRange)
		{
			DrawDebugLine(GetWorld(), CurrentLocation, PlayerLocation, FColor::Blue, false, -1, 0, 12.333);
			bInLassoRange = true;
			bInFleeRange = false;
			bInAttackRange = false;
		}
	}

	if (PlayerCharacter == NULL)
	{
		UE_LOG(LogTemp, Display, TEXT("WE ARE NOT IN THE BEAM"));
	}
	return false;
}

CharacterState::StatusEffect ASheriffAI::GetStatusEffect()
{
	return Super::GetStatusEffect();
}

bool ASheriffAI::GetbIsInHardCC()
{
	return Super::GetbIsInHardCC();
}

bool ASheriffAI::GetbIsInSoftCC()
{
	return Super::GetbIsInSoftCC();
}

void ASheriffAI::Destroyed()
{
	return Super::Destroyed();
}

SheriffState ASheriffAI::GetSheriffState()
{
	return CurrentState;
}

bool ASheriffAI::bIsSoftCC()
{
	return Super::bIsSoftCC();
}

bool ASheriffAI::bIsHardCC()
{
	return Super::bIsHardCC();
}

void ASheriffAI::Die()
{
	return Super::Die();
}

AWeapon* ASheriffAI::EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip)
{
	return Super::EquipNewWeapon(WeaponToEquip);
}

void ASheriffAI::Flee()
{

}

void ASheriffAI::SetSheriffState(SheriffState NewStateToEnter)
{
	CurrentState = NewStateToEnter;
}

void ASheriffAI::Aim(ACharacterController* PlayerToAimAt)
{
	//FixedWeaponRotation();
	FVector Direction = PlayerToAimAt->GetActorLocation() - GetActorLocation();
	FRotator NewRollRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	SetActorRotation(NewRollRotation);
}

void ASheriffAI::Shoot()
{
	//UE_LOG(LogTemp, Display, TEXT("Attemping to shoot"));
}

void ASheriffAI::Casting()
{
	UE_LOG(LogTemp, Display, TEXT("Attempting to cast lasso"));
}

void ASheriffAI::Lasso()
{
	UE_LOG(LogTemp, Display, TEXT("Completed Lasso task"));
	//CurrentlyEquippedWeapon = GetEquippedWeapon();
	//if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
	//{
	//	if (BlackboardComponent->GetValueAsObject(TEXT("Target")) != NULL)
	//	{
	//		if (ACharacterController* PlayerReference = Cast<ACharacterController>(BlackboardComponent->GetValueAsObject(TEXT("Target"))))
	//		{
	//			CurrentLocation = GetActorLocation();
	//			PlayerLocation = PlayerReference->GetActorLocation();
	//			DistanceToPlayer = FVector::Dist(CurrentLocation, PlayerLocation);

	//			//If the player gets pulled into the Sheriff's knife attack range, he will let go of the rope to swing his knife
	//			CushionSpace = KnifeAttackRange;

	//			if (DistanceToPlayer > CushionSpace)
	//			{
	//				LassoCableComponent->CableLength = LassoLength;
	//				LassoCableComponent->SetAttachEndTo(PlayerReference, GetMesh()->GetSocketBoneName("pelvis"));
	//				FVector PullDirecton = PullingVelocity * (PlayerReference->GetActorLocation() - GetActorLocation());
	//				PlayerReference->GetMovementComponent()->AddInputVector(PullDirecton);

	//				AddStatusEffect(UStatusEffect_SoftCrowdControl::StaticClass(), false, 2.f, 0.f, this);
	//			}

	//			if (DistanceToPlayer < CushionSpace)
	//			{
	//				LassoCableComponent->SetAttachEndTo(this, GetMesh()->GetSocketBoneName("hand_r"));
	//			}
	//		}
	//	}
	//}
}

void ASheriffAI::EndLasso()
{
	UE_LOG(LogTemp, Display, TEXT("Ended Lasso task"));
	SetSheriffState(SheriffState::IDLE);
}