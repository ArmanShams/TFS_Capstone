// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "MinerAI.h"
#include "AIController.h"
#include "MinerAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BrainComponent.h"

AMinerAI::AMinerAI()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Health = MAXHEALTH;

	MoveSpeed = .04f;

	TurnRate = 0.25f;

	MaxRange = 100.0f;

	AttackFrequency = 5.f;

	AttackRange = 250.0f;

	ChargeDamage = 45.f;

	DistanceToUseCharge = 1500.f;

	ArrowSpawnOffset = 150.f;

	ChargeSpeed = 1500.f;


	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ThisClass::OnCollision);

	// Replace with new weapon asset for respective enemy type.
	ConstructorHelpers::FClassFinder<AWeapon>WeaponAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/KnifeBP_Arman.KnifeBP_Arman_C'"));

	if (WeaponAsset.Class)
	{
		//UE_LOG(LogTemp, Display, TEXT("WE HAVE FOUND THE CLASS"));
		DefaultWeapon = (UClass*)WeaponAsset.Class;
	}
	// Get the arrow to be projected on the ground.
	ConstructorHelpers::FClassFinder<AActor>DecalActor(TEXT("Blueprint'/Game/Blueprints/Enemies/Miner/MinerVisualTelegraph_ChargeBP.MinerVisualTelegraph_ChargeBP_C'"));
	if (DecalActor.Class)
	{
		//UE_LOG(LogTemp, Display, TEXT("WE HAVE FOUND THE ARROW CLASS"));
		ArrowDecalClass = (UClass*)DecalActor.Class;
	}
}

void AMinerAI::BeginPlay()
{
	Super::BeginPlay();
	CurrentState = MinerState::IDLE;
}

void AMinerAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//if (TimeSinceLastCharge <= ChargeCooldown)
	//{
	//	TimeSinceLastCharge += DeltaSeconds;
	//}
	//

	switch (CurrentState)
	{
	case MinerState::IDLE:

		//GetMesh()->SetWorldRotation(FRotator(GetMesh()->GetComponentRotation().Pitch, MeshYawOffSet, GetMesh()->GetComponentRotation().Roll));

		break;
	case MinerState::READYING:
			if (AActor* ValidTarget = Cast<AActor>(Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent()->GetValueAsObject(TEXT("Target"))))
			{
				FRotator CurrentRotation = GetActorRotation();
				FVector CurrentLocation = RootComponent->GetComponentLocation();
				FVector CurrentTargetLocation = ValidTarget->GetActorLocation();

				FVector Diff = FVector(CurrentTargetLocation.X - CurrentLocation.X, CurrentTargetLocation.Y - CurrentLocation.Y, 0.f);
				
				SetActorRotation(FMath::Lerp(CurrentRotation, FRotator(0.f, Diff.Rotation().Yaw, 0.f), 0.2f));
			}

			// Re orients the Miner's visual telegraph as he gets ready to charge.
			if (ArrowDecalActor != NULL)
			{
				//if (ArrowDecalActor->GetLifeSpan() > 0.1f)
				{
					if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
					{
						FRotator CurrentRotation = ArrowDecalActor->GetActorRotation();
						FVector CurrentLocation = GetActorLocation();
						FVector CurrentTargetLocation = Cast<ACharacter>(BlackboardComponent->GetValue<UBlackboardKeyType_Object>(TEXT("Target")))->GetRootComponent()->GetComponentLocation();
						FVector Diff = FVector(CurrentTargetLocation.X - CurrentLocation.X, CurrentTargetLocation.Y - CurrentLocation.Y, CurrentTargetLocation.Z - CurrentLocation.Z);

						ArrowDecalActor->SetActorRotation(FMath::Lerp(CurrentRotation, FRotator(CurrentRotation.Pitch, Diff.Rotation().Yaw, CurrentRotation.Roll), 0.2f));
						//ArrowDecalActor->SetActorRotation(FRotator(CurrentRotation.Pitch, Diff.Rotation().Yaw, CurrentRotation.Roll));
					}
				}
			}
		break;
	case MinerState::CHARGING:
		// TO ADD: Running at things.
		GetMovementComponent()->AddInputVector(GetActorForwardVector() * ChargeSpeed);
		
		break;
	case MinerState::ATTACKING:

		break;
	default:
		break;
	}
		
	if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
	{
		BlackboardComponent->SetValueAsBool(TEXT("IsHardCC"), bIsHardCC());
		BlackboardComponent->SetValueAsBool(TEXT("IsSoftCC"), bIsSoftCC());
		BlackboardComponent->SetValueAsBool(TEXT("IsInMeleeRange"), bIsInRange());
		BlackboardComponent->SetValueAsBool(TEXT("IsInRangeToCharge"), bIsInRange(DistanceToUseCharge));
		BlackboardComponent->SetValueAsEnum(TEXT("StatusEffect"), Effects);
		BlackboardComponent->SetValueAsEnum(TEXT("EnemyState"), (uint8)CurrentState);

		if (BlackboardComponent->GetValueAsBool(TEXT("MarkedToReturnToIdleState")))
		{
			BlackboardComponent->SetValueAsBool(TEXT("MarkedToReturnToIdleState"), false);
		}
		if (!bIsHardCC())
		{
			//UE_LOG(LogTemp, Display, TEXT("I AIN'T HARD CC"));
		}

	}
}

void AMinerAI::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

float AMinerAI::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

bool AMinerAI::bIsInRange()
{
	return Super::bIsInRange(AttackRange);
}

bool AMinerAI::bIsInRange(float OveriddenDesiredRange)
{
	return Super::bIsInRange(OveriddenDesiredRange);
}

AWeapon* AMinerAI::GetEquippedWeapon()
{
	return Super::GetEquippedWeapon();
}

bool AMinerAI::bIsSoftCC()
{
	return Super::bIsSoftCC();
}

bool AMinerAI::bIsHardCC()
{
	return Super::bIsHardCC();
}

bool AMinerAI::GetBTIsInRange()
{
	if (HasActorBegunPlay() && CurrentState == MinerState::ATTACKING)
	{
		UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent();
		return BlackboardComponent->GetValueAsBool(TEXT("IsInMeleeRange"));
	}
	return false;
}
	

MinerState AMinerAI::GetMinerState()
{
	return CurrentState;
}

void AMinerAI::StartCharge()
{
	if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
	{
		ArrowDecalActor = GetWorld()->SpawnActor<AActor>(ArrowDecalClass);
		//ArrowDecalActor->SetActorRelativeRotation(FRotator(-90.f, 90.f, 0.f));
		ArrowDecalActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
		//ArrowDecalActor->SetLifeSpan(ChargeCooldown);
		Effects = CharacterState::INTERRUPTABLE;
		CurrentState = MinerState::READYING;
	}
}

void AMinerAI::Charge()
{
	if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
	{
		ArrowDecalActor->SetLifeSpan(0.2f);
		ArrowDecalActor = NULL;
		//CurrentState = MinerState::CHARGING;
		Effects = CharacterState::UNSTOPPABLE;
		CurrentState = MinerState::CHARGING;
	}
}

void AMinerAI::SetStatusEffect(CharacterState::StatusEffect NewStatusEffect)
{
	Super::SetStatusEffect(NewStatusEffect);
}

void AMinerAI::SetMinerState(MinerState NewStateToEnter)
{
	UE_LOG(LogTemp, Display, TEXT("Altering miner state"));
	CurrentState = NewStateToEnter;
}

void AMinerAI::Attack()
{
	CurrentState = MinerState::ATTACKING;
}

CharacterState::StatusEffect AMinerAI::GetStatusEffect()
{
	return Super::GetStatusEffect();
}

void AMinerAI::EquipWeapon(TSubclassOf<AWeapon> WeaponToEquip)
{
	Super::EquipWeapon(WeaponToEquip);
}

void AMinerAI::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	UE_LOG(LogTemp, Display, TEXT("The miner ran into something."));

}
