// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "BearTrap.h"
#include "EnemyAI/BountyHunter/BountyHunter.h"
#include "Character/CharacterController.h"
#include "Engine.h"


ABearTrap::ABearTrap()
{
	PrimaryActorTick.bCanEverTick = true;
	TrapCollider = CreateDefaultSubobject<USphereComponent>(TEXT("TrapCollider"));
	TrapCollider->AttachTo(RootComponent);
	radius = 30.f;
	Damage = 5;
	TrapCollider->SetCollisionProfileName(TEXT("Traps"));
	TrapCollider->SetSphereRadius(radius);
	TrapCollider->OnComponentBeginOverlap.AddDynamic(this, &ABearTrap::OnComponentBeginOverlap);
	TrapCollider->OnComponentEndOverlap.AddDynamic(this, &ABearTrap::OnComponentEndOverlap);

	BountyHunter = Cast<ABountyHunter>(GetClass());
}

void ABearTrap::BeginPlay()
{
	Super::BeginPlay();
	SetOwner(BountyHunter);
}

void ABearTrap::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	// UE_LOG(LogTemp, Display, TEXT("The bear trap has been hidden"));
	// this->SetActorHiddenInGame(true);
}


void ABearTrap::SetOwner(AActor* NewOwner)
{
	UE_LOG(LogTemp, Display, TEXT("The new owner of the Bear Trap is now the Bounty Hunter"));
	NewOwner = BountyHunter;
}

void ABearTrap::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// this->SetActorHiddenInGame(false);
		UE_LOG(LogTemp, Display, TEXT("You've stepped on a trap"));
}

void ABearTrap::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
		UE_LOG(LogTemp, Display, TEXT("The trap activated and applied damage to you"));
		UGameplayStatics::ApplyDamage(OtherActor, Damage, GetWorld()->GetFirstPlayerController(), this, TSubclassOf<UDamageType>());
		UE_LOG(LogTemp, Display, TEXT("The trap was used and now is destroyed"));
		Destroy();
}