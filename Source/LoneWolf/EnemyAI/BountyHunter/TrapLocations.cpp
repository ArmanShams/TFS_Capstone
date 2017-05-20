// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "TrapLocations.h"

ATrapLocations::ATrapLocations()
{
	PrimaryActorTick.bCanEverTick = true;
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	bIsOccupied = false;
}

void ATrapLocations::BeginPlay()
{
	Super::BeginPlay();
}

void ATrapLocations::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}