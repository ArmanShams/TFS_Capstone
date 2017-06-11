// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "MinerAI.h"
#include "AIController.h"
#include "MinerAnimInstance.h"
#include "Weapons/Weapon.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BrainComponent.h"
#include "Character/PlayerCharacter/CharacterController.h"
#include "Character/StatusEffects/StatusEffect_HardCrowdControl.h"

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

	MinimumChargeDistance = 500.f;

	ArrowSpawnOffset = 150.f;

	ChargeSpeed = 2000.f;

	DistanceToUseStomp = 200.f;

	StompDamage = 20.f;

	StompRadius = 88.f;

	ChargeLaunchDistance = 20.f;

	StompStunDuration = 1.5f;

	PostChargeSelfStunDuration = 7.0f;

	bChargeHasDamagedPlayer = false;

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ThisClass::OnCollision);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap);

	// Replace with new weapon asset for respective enemy type.
	ConstructorHelpers::FClassFinder<AWeapon>WeaponAsset(TEXT("Blueprint'/Game/Blueprints/Weapons/Miner/MinerPickAxe.MinerPickAxe_C'"));

	if (WeaponAsset.Class)
	{
		//UE_LOG(LogTemp, Display, TEXT("WE HAVE FOUND THE CLASS"));
		DefaultWeapon = (UClass*)WeaponAsset.Class;
	}
	// Get the arrow to be projected on the ground.
	ConstructorHelpers::FClassFinder<AActor>DecalArrowActor(TEXT("Blueprint'/Game/Blueprints/Enemies/MinerAI/MinerVisualTelegraph_ChargeBP.MinerVisualTelegraph_ChargeBP_C'"));
	if (DecalArrowActor.Class)
	{
		//UE_LOG(LogTemp, Display, TEXT("WE HAVE FOUND THE ARROW CLASS"));
		ArrowDecalClass = (UClass*)DecalArrowActor.Class;
	}
	
	ConstructorHelpers::FClassFinder<AActor>DecalCircleActor(TEXT("Blueprint'/Game/Blueprints/Enemies/MinerAI/MinerVisualTelegraph_StompBP.MinerVisualTelegraph_StompBP_C'"));
	if (DecalCircleActor.Class)
	{
		//UE_LOG(LogTemp, Display, TEXT("WE HAVE FOUND THE ARROW CLASS"));
		StompDecalActorClass = (UClass*)DecalCircleActor.Class;
	}
}

void AMinerAI::BeginPlay()
{
	Super::BeginPlay();
	EquipNewWeapon(DefaultWeapon);
	CurrentState = MinerState::IDLE;
	DefaultMoveSpeed = Cast<UCharacterMovementComponent>(GetMovementComponent())->MaxWalkSpeed;
	//UE_LOG(LogTemp, Display, TEXT("Miner melee weapon default collision profile  = %s"), CurrentlyEquippedWeapon->);
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
	case MinerState::READYINGCHARGE:
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
	case MinerState::READYINGSTOMP:
		if (StompDecalActor != NULL)
		{

		}
		break;
	case MinerState::CHARGING:
		GetMovementComponent()->AddInputVector(GetActorForwardVector() * ChargeSpeed);

		break;
	case MinerState::ATTACKING:

		break;
	default:
		break;
	}
		
	if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
	{
		BlackboardComponent->SetValueAsBool(TEXT("IsHardCC"), bIsInHardCC);
		BlackboardComponent->SetValueAsBool(TEXT("IsSoftCC"), bIsInSoftCC);
		BlackboardComponent->SetValueAsBool(TEXT("IsInMeleeRange"), bIsInRange());

		if (bIsInRange(DistanceToUseCharge))
		{
			if (AActor* RecastTarget = Cast<AActor>(BlackboardComponent->GetValueAsObject("Target")))
			{
				FVector DistanceVector = RecastTarget->GetActorLocation() - GetActorLocation();
				if (DistanceVector.Size() >= MinimumChargeDistance)
				{
					BlackboardComponent->SetValueAsBool(TEXT("IsInRangeToCharge"), bIsInRange(DistanceToUseCharge));
				}
			}
		}
		BlackboardComponent->SetValueAsBool(TEXT("IsInRangeToStomp"), bIsInRange(DistanceToUseStomp));
		BlackboardComponent->SetValueAsEnum(TEXT("StatusEffect"), Effects);
		BlackboardComponent->SetValueAsEnum(TEXT("EnemyState"), (uint8)CurrentState);

		if (BlackboardComponent->GetValueAsBool(TEXT("MarkedToReturnToIdleState")))
		{
			BlackboardComponent->SetValueAsBool(TEXT("MarkedToReturnToIdleState"), false);
		}
		if (bIsHardCC())
		{
			//UE_LOG(LogTemp, Display, TEXT("I AM HARD CC"));
		}
	}

	//DrawDebugLine(GetWorld(), RootComponent->GetComponentLocation(), RootComponent->GetComponentLocation() + GetActorForwardVector() * 50.f , FColor(255, 255, 255), true, -1, 0, 12.333);
}

void AMinerAI::SetupPlayerInputComponent(class UInputComponent* InInputComponent)
{
	Super::SetupPlayerInputComponent(InInputComponent);
}

void AMinerAI::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, float LifeTime, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::AddStatusEffect(ClassToCreateFrom, bShouldPerformTickAction, LifeTime, TickRate, CharacterThatInflictedStatusEffect);
	if (ClassToCreateFrom->GetClass() == UStatusEffect_HardCrowdControl::StaticClass())
	{
	
			if (ArrowDecalActor != NULL)
			{
				ArrowDecalActor->SetOwner(NULL);
				ArrowDecalActor->SetLifeSpan(0.001f);
				ArrowDecalActor = NULL;
			}
			if (StompDecalActor != NULL)
			{
				StompDecalActor->SetOwner(NULL);
				StompDecalActor->SetLifeSpan(0.001f);
				StompDecalActor = NULL;
			}
			Effects = CharacterState::NONE;
			CurrentState = MinerState::IDLE;
		
	}
}

void AMinerAI::AddStatusEffect(TSubclassOf<class UStatusEffectBase> ClassToCreateFrom, bool bShouldPerformTickAction, bool bShouldDealDamage, float LifeTime, float DamageToDeal, float TickRate, ALoneWolfCharacter* CharacterThatInflictedStatusEffect)
{
	Super::AddStatusEffect(ClassToCreateFrom, bShouldPerformTickAction, bShouldDealDamage, LifeTime, DamageToDeal, TickRate, CharacterThatInflictedStatusEffect);
	if (ClassToCreateFrom->GetClass() == UStatusEffect_HardCrowdControl::StaticClass())
	{
		if (ArrowDecalActor != NULL)
		{
			ArrowDecalActor->SetOwner(NULL);
			ArrowDecalActor->SetLifeSpan(0.001f);
			ArrowDecalActor = NULL;
		}
		if (StompDecalActor != NULL)
		{
			StompDecalActor->SetOwner(NULL);
			StompDecalActor->SetLifeSpan(0.001f);
			StompDecalActor = NULL;
		}
			Effects = CharacterState::NONE;
			CurrentState = MinerState::IDLE;
	}
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

bool AMinerAI::GetbIsInHardCC()
{
	return Super::GetbIsInHardCC();
}

bool AMinerAI::GetbIsInSoftCC()
{
	return Super::GetbIsInSoftCC();
}

bool AMinerAI::bIsSoftCC()
{
	return Super::bIsSoftCC();
}

bool AMinerAI::bIsHardCC()
{
	return Super::bIsHardCC();
}

void AMinerAI::Die()
{
	if (ArrowDecalActor != NULL)
	{
		ArrowDecalActor->SetOwner(NULL);
		ArrowDecalActor->SetLifeSpan(0.001f);
		ArrowDecalActor = NULL;
	}
	if (StompDecalActor != NULL)
	{
		StompDecalActor->SetOwner(NULL);
		StompDecalActor->SetLifeSpan(0.001f);
		StompDecalActor = NULL;
	}
	CurrentState = MinerState::DEAD;
	Super::Die();
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

AWeapon* AMinerAI::EquipNewWeapon(TSubclassOf<class AWeapon> WeaponToEquip)
{
	CurrentlyEquippedWeapon = Super::EquipNewWeapon(WeaponToEquip);
	CurrentlyEquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("hand_r"));
	CurrentlyEquippedWeapon->SetActorRelativeRotation(FRotator(14.3f, -32.f,-25.f));
	CurrentlyEquippedWeapon->SetActorRelativeLocation(FVector(-11.364f, 5.825f, 6.f));
	return CurrentlyEquippedWeapon;
	//CurrentlyEquippedWeapon->SetActorLocation(GetMesh()->GetSocketLocation(FName("hand_r")));
	//CurrentlyEquippedWeapon->SetActorRelativeRotation(FRotator(30.f, -90.f, 90.f));
}

void AMinerAI::StartCharge()
{
	if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
	{
		ArrowDecalActor = GetWorld()->SpawnActor<AActor>(ArrowDecalClass);
		//ArrowDecalActor->SetActorRelativeRotation(FRotator(-90.f, 90.f, 0.f));
		ArrowDecalActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
		ArrowDecalActor->SetOwner(this);
		//ArrowDecalActor->SetLifeSpan(ChargeCooldown);
		Effects = CharacterState::INTERRUPTABLE;
		CurrentState = MinerState::READYINGCHARGE;
		Cast<UCharacterMovementComponent>(GetMovementComponent())->MaxWalkSpeed = ChargeSpeed;
	}
}

void AMinerAI::Charge()
{
	if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
	{
		ArrowDecalActor->SetLifeSpan(0.2f);
		ArrowDecalActor->SetOwner(NULL);
		ArrowDecalActor = NULL;
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Overlap);
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
	if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
	{
		if (AActor* RecastTarget = Cast<AActor>(BlackboardComponent->GetValueAsObject("Target")))
		{
			FVector TargetLocation = RecastTarget->GetActorLocation();
			FVector DirectionToTarget = TargetLocation - GetActorLocation();
			FRotator NewRotation = GetActorRotation();
			NewRotation.Yaw = DirectionToTarget.Rotation().Yaw;

			SetActorRotation(NewRotation);
		}
	}
}

void AMinerAI::StartStomp()
{
	if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
	{
		StompDecalActor = GetWorld()->SpawnActor<AActor>(StompDecalActorClass);
		StompDecalActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
		StompDecalActor->SetOwner(this);
		Effects = CharacterState::INTERRUPTABLE;
		CurrentState = MinerState::READYINGSTOMP;
	}
}

void AMinerAI::Stomp()
{
	if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
	{
		StompDecalActor->SetLifeSpan(0.2f);
		StompDecalActor->SetOwner(NULL);
		StompDecalActor = NULL;
		
		if (UGameplayStatics::ApplyRadialDamage(this, StompDamage, GetActorLocation(), StompRadius, UDamageType::StaticClass(), TArray<AActor*>(), this, GetController()))
		{
			TArray<FOverlapResult> HitResult;
			GetWorld()->OverlapMultiByObjectType(HitResult, GetActorLocation(), FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(StompRadius), FCollisionQueryParams());
			//DrawDebugSphere(GetWorld(), GetActorLocation(), StompRadius, 32, FColor::Red, false, 1.5f);
			for (size_t i = 0; i < HitResult.Num(); i++)
			{
				if (ALoneWolfCharacter* RecastedResult = Cast<ALoneWolfCharacter>(HitResult[i].GetActor()))
				{
					if (HitResult[i].GetActor() != this)
					{
						RecastedResult->AddStatusEffect(UStatusEffect_HardCrowdControl::StaticClass(), false, StompStunDuration, 0.f, this);
					}
				}
			}
		}
		Effects = CharacterState::NONE;
		CurrentState = MinerState::IDLE;
	}
}

CharacterState::StatusEffect AMinerAI::GetStatusEffect()
{
	return Super::GetStatusEffect();
}

void AMinerAI::Destroyed()
{
	Super::Destroyed();
}

void AMinerAI::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FHitResult OutHit = FHitResult();
	const FCollisionQueryParams Params = FCollisionQueryParams();
	const FCollisionResponseParams ResponseParam = FCollisionResponseParams();

	if (CurrentState == MinerState::CHARGING)
	{
		TArray<FHitResult> HitResults;
		FCollisionShape CollisionShape = FCollisionShape::MakeSphere(50.f);
		if (GetWorld()->SweepMultiByChannel(HitResults,
			RootComponent->GetComponentLocation(),
			RootComponent->GetComponentLocation() + GetActorForwardVector() * 50.f,
			GetActorRotation().Quaternion(),
			ECC_GameTraceChannel5,
			CollisionShape,
			Params,
			ResponseParam))
		{
			if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
			{
				BlackboardComponent->SetValueAsBool(TEXT("MarkedToReturnToIdleState"), true);
				UE_LOG(LogTemp, Display, TEXT("Sweep returned a blocking hit when the miner was charging, miner hit something."));
				CurrentState = MinerState::IDLE;
				//SetActorRelativeRotation(FRotator(GetActorRotation().Pitch, -GetActorRotation().Yaw, GetActorRotation().Roll));
				GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
				GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Block);
				GetMovementComponent()->StopActiveMovement();
				Cast<UCharacterMovementComponent>(GetMovementComponent())->MaxWalkSpeed = DefaultMoveSpeed;

				AddStatusEffect(UStatusEffect_HardCrowdControl::StaticClass(), false, PostChargeSelfStunDuration, 0.f, this);
			}
		}
		
		//if (GetWorld()->LineTraceSingleByChannel(OutHit, RootComponent->GetComponentLocation(), RootComponent->GetComponentLocation() + GetActorForwardVector() * 50.f, ECC_GameTraceChannel5, Params, ResponseParam))
		//{
		//	DrawDebugLine(GetWorld(), RootComponent->GetComponentLocation(), RootComponent->GetComponentLocation() + GetActorForwardVector() * 50.f, FColor(255, 255, 255), true, -1, 0, 12.333);
		//	DrawDebugLine(GetWorld(), RootComponent->GetComponentLocation(), OutHit.Location, FColor(0, 255, 0), true, -1, 0, 12.333);
		//	//Effects = CharacterState::NONE;
		//	//DrawDebugLine(GetWorld(), GetActorLocation(), GetMesh()->GetForwardVector() * 15.f, FColor(255, 0, 0), true, -1, 0, 12.333);
		//	//DrawDebugLine(GetWorld(), RootComponent->GetComponentLocation(), OutHit.Location, FColor(0, 255, 0), true, -1, 0, 12.333);
		//	
		//
		//	if (UBlackboardComponent* BlackboardComponent = Cast<AAIController>(GetController())->GetBrainComponent()->GetBlackboardComponent())
		//	{
		//		BlackboardComponent->SetValueAsBool(TEXT("MarkedToReturnToIdleState"), true);
		//		UE_LOG(LogTemp, Display, TEXT("Miner hit a %s"), *OutHit.GetActor()->GetName());
		//		CurrentState = MinerState::IDLE;
		//		//SetActorRelativeRotation(FRotator(GetActorRotation().Pitch, -GetActorRotation().Yaw, GetActorRotation().Roll));
		//		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
		//		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Block);
		//		GetMovementComponent()->StopActiveMovement();
		//		Cast<UCharacterMovementComponent>(GetMovementComponent())->MaxWalkSpeed = DefaultMoveSpeed;
		//
		//		AddStatusEffect(UStatusEffect_HardCrowdControl::StaticClass(), false, PostChargeSelfStunDuration, 0.f, this);
		//	}
		//}
	}
}

void AMinerAI::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CurrentState ==  MinerState::CHARGING)
	{
		if (ALoneWolfCharacter* RecastedActor = Cast<ALoneWolfCharacter>(OtherActor))
		{
			FVector DirectionToLaunch = 2.f * (RecastedActor->GetActorLocation() - GetActorLocation()); RecastedActor->LaunchCharacter(DirectionToLaunch * ChargeLaunchDistance, true, true);

			if (ACharacterController* CastedAsPlayer = Cast<ACharacterController>(RecastedActor))
			{
				UE_LOG(LogTemp, Display, TEXT("The miner overlapped something."));
				UGameplayStatics::ApplyDamage(RecastedActor, ChargeDamage, GetController(), this, TSubclassOf<UDamageType>());
				bChargeHasDamagedPlayer = true;
				//DirectionToLaunch.Normalize();
			}
			if (bChargeHasDamagedPlayer)
			{
				GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
				GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Block);
				GetMovementComponent()->StopActiveMovement();
				Cast<UCharacterMovementComponent>(GetMovementComponent())->MaxWalkSpeed = DefaultMoveSpeed;
				Effects = CharacterState::NONE;
				CurrentState = MinerState::IDLE;
			}
		}
	}
}
