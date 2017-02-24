// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "BearTrap.h"
#include "Engine.h"


// Sets default values
ABearTrap::ABearTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABearTrap::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
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
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::White, FString::Printf(TEXT("You've stepped on a bear trap!")));
}

