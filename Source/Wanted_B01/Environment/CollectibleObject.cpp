// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "CollectibleObject.h"
#include "Engine.h"

ACollectibleObject::ACollectibleObject()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Create a collider component so that we can check if anything comes into collision with it
	ColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ColliderComponent"));
	RootComponent = ColliderComponent;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));

	//MeshComponent->AttachTo(ColliderComponent);
	//AttachTo function is deprecated for this build version, use AttachToComponent
		//YourComp->AttachToComponent(OtherComp, FAttachmentTransformRules::KeepWorldTransform) or KeepRelativeTransform
	MeshComponent->AttachToComponent(ColliderComponent, FAttachmentTransformRules::KeepWorldTransform);
	MovementComponent = CreateDefaultSubobject<UMovementComponent>(TEXT("Movement Component"));

	//Set up a notification for when this component overlaps something
	ColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &ACollectibleObject::OnOverlapBegin);

}

void ACollectibleObject::BeginPlay()
{
	Super::BeginPlay();
}

void ACollectibleObject::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ACollectibleObject::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
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


