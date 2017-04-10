// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "BearTrap.h"
#include "EnemyAI/BountyHunter/BountyHunter.h"
#include "Engine.h"


ABearTrap::ABearTrap()
{
	PrimaryActorTick.bCanEverTick = true;
	BountyHunterRef = Cast<ABountyHunter>(GetClass());
}

void ABearTrap::BeginPlay()
{
	Super::BeginPlay();
}

void ABearTrap::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ABearTrap::damageToPlayer()
{
}

void ABearTrap::effectToPlayer()
{
}

void ABearTrap::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("You've stepped on a trap"));
}

void ABearTrap::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("The trap activated"));
}