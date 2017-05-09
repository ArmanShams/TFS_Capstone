// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "CollectibleObject.h"
#include "Engine.h"

ACollectibleObject::ACollectibleObject()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create a collider component so that we can check if anything comes into collision with it
	ColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ColliderComponent"));
	RootComponent = ColliderComponent;

	CollectibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollectibleMeshComponent"));
	CollectibleMesh->SetupAttachment(ColliderComponent);

	ColliderComponent->OnComponentHit.AddDynamic(this, &ACollectibleObject::OnHit);
}

void ACollectibleObject::BeginPlay()
{
	Super::BeginPlay();
}

void ACollectibleObject::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ACollectibleObject::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this))
	{
		//On Screen Debug Message (#include "Engine.h")
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::White, FString::Printf(TEXT("You have collided with Collectible Object!")));
		
		//Destroy the actor
		//Destroy();
		
		//Set a lifespan to 5 seconds
		//SetLifeSpan(5);
	}
}


