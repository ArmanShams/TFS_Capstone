// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BearTrap.h"
#include "EnemyAI/BountyHunter/BountyHunter.h"
#include "EnemyAI/BountyHunter/TrapLocations.h"
#include "Character/PlayerCharacter/CharacterController.h"
#include "Character/StatusEffects/StatusEffect_SoftCrowdControl.h"
#include "Engine.h"

ABearTrap::ABearTrap()
{
	PrimaryActorTick.bCanEverTick = true;
	
	TrapCollider = CreateDefaultSubobject<USphereComponent>(TEXT("TrapCollider"));
	TrapCollider->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> BearTrapSkeletalMesh(TEXT("SkeletalMesh'/Game/Geometry/World/M_BearTrap.M_BearTrap'"));
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	//MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetupAttachment(TrapCollider);
	MeshComponent->SetSkeletalMesh(BearTrapSkeletalMesh.Object);
	Mesh = BearTrapSkeletalMesh.Object;

	radius = 100.f;
	Damage = 5;
	TrapCollider->SetCollisionProfileName(TEXT("Traps"));
	TrapCollider->SetSphereRadius(radius);
	
	RootComponent = TrapCollider;
}

void ABearTrap::BeginPlay()
{
	Super::BeginPlay();
	TrapCollider->OnComponentBeginOverlap.AddDynamic(this, &ABearTrap::OnComponentBeginOverlap);
	TrapCollider->OnComponentEndOverlap.AddDynamic(this, &ABearTrap::OnComponentEndOverlap);
}

void ABearTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABearTrap::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);
}

void ABearTrap::Destroyed()
{
	Super::Destroyed();
}

void ABearTrap::SetLocationBeingOccupied(class ATrapLocations* NewLocationBeingOccupied)
{
	LocationBeingOccupied = NewLocationBeingOccupied;
	LocationBeingOccupied->bIsOccupied = true;
}

void ABearTrap::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACharacterController* Player = Cast<ACharacterController>(OtherActor))
	{
		this->SetActorHiddenInGame(false);
		SetActorLocation(Player->GetMesh()->GetComponentLocation());
		MeshComponent->SetRelativeLocation(FVector::ZeroVector);
		Player->AddStatusEffect(UStatusEffect_SoftCrowdControl::StaticClass(), false, 0.25f, 0.f, Cast<ALoneWolfCharacter>(Player));
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("You've stepped on a bear trap, dodge to avoid snapping your legs!")));
	}
}

void ABearTrap::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ACharacterController* Player = Cast<ACharacterController>(OtherActor))
	{
		AActor* OwningActor = GetOwner();
		if (OwningActor != NULL)
		{
			if (APawn* RecastedOwner = Cast<APawn>(OwningActor))
			{
				UGameplayStatics::ApplyDamage(OtherActor, Damage, RecastedOwner->GetController(), this, TSubclassOf<UDamageType>());
				Player->AddStatusEffect(UStatusEffect_SoftCrowdControl::StaticClass(), false, 2.4f, 0.f, Cast<ALoneWolfCharacter>(RecastedOwner));

				if (ABountyHunter* RecastToBountyHunter = Cast<ABountyHunter>(RecastedOwner))
				{
					RecastToBountyHunter->DecrementActiveBearTraps(this);
				}
			}
		}
		else
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, GetWorld()->GetFirstPlayerController(), this, TSubclassOf<UDamageType>());
			Player->AddStatusEffect(UStatusEffect_SoftCrowdControl::StaticClass(), false, 2.4f, 0.f, Cast<ALoneWolfCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()));
		}
		if (LocationBeingOccupied != NULL)
		{
			LocationBeingOccupied->bIsOccupied = false;
		}
		Destroy();
	}
}