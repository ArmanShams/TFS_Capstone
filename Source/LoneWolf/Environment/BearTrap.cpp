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
	MeshComponent->SetupAttachment(TrapCollider);
	MeshComponent->SetSkeletalMesh(BearTrapSkeletalMesh.Object);

	radius = 30.f;
	Damage = 5;
	TrapCollider->SetCollisionProfileName(TEXT("Traps"));
	TrapCollider->SetSphereRadius(radius);
	TrapCollider->OnComponentBeginOverlap.AddDynamic(this, &ABearTrap::OnComponentBeginOverlap);
	TrapCollider->OnComponentEndOverlap.AddDynamic(this, &ABearTrap::OnComponentEndOverlap);
	//bIsVisible = false;
	BountyHunter = NULL;
}

void ABearTrap::BeginPlay()
{
	Super::BeginPlay();
}

void ABearTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (bIsVisible)
	//{
	//	this->SetActorHiddenInGame(false);
	//}
}

void ABearTrap::SetOwner(AActor* NewOwner)
{
	NewOwner = BountyHunter;
}

void ABearTrap::Destroyed()
{
	if (LocationBeingOccupied != NULL)
	{
		LocationBeingOccupied->bIsOccupied = false;
	}
	Super::Destroyed();
}

void ABearTrap::SetLocationBeingOccupied(class ATrapLocations* NewLocationBeingOccupied)
{
	LocationBeingOccupied = NewLocationBeingOccupied;
}

void ABearTrap::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACharacterController* Player = Cast<ACharacterController>(OtherActor))
	{
		UE_LOG(LogTemp, Display, TEXT("You've stepped on a trap"));
	}
}

void ABearTrap::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ACharacterController* Player = Cast<ACharacterController>(OtherActor))
	{
		// bIsVisible = true;
		// this->SetActorHiddenInGame(true);
		UE_LOG(LogTemp, Display, TEXT("The trap activated and applied damage to you"));
		if (BountyHunter != NULL)
		{
			if (APawn* RecastedOwner = Cast<APawn>(BountyHunter))
			{
				UGameplayStatics::ApplyDamage(OtherActor, Damage, BountyHunter->GetController(), this, TSubclassOf<UDamageType>());
				Player->AddStatusEffect(UStatusEffect_SoftCrowdControl::StaticClass(), false, 2.4f, 0.f, Cast<ALoneWolfCharacter>(BountyHunter));
			}
		}
		else
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, GetWorld()->GetFirstPlayerController(), this, TSubclassOf<UDamageType>());
			Player->AddStatusEffect(UStatusEffect_SoftCrowdControl::StaticClass(), false, 2.4f, 0.f, Cast<ALoneWolfCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()));
		}
		Destroy();
	}
}