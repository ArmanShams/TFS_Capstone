// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "MolotovProjectile.h"


// Sets default values
AMolotovProjectile::AMolotovProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMolotovProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMolotovProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AMolotovProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
}

