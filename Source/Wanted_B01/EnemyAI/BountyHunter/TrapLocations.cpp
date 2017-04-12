// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "TrapLocations.h"

ATrapLocations::ATrapLocations()
{
	PrimaryActorTick.bCanEverTick = true;
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	UE_LOG(LogTemp, Display, TEXT("The trap location is not occupied"));
	bIsOccupied = false;
}

void ATrapLocations::BeginPlay()
{
	Super::BeginPlay();
}

void ATrapLocations::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}