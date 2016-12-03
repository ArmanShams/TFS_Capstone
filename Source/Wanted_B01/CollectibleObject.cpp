// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "CollectibleObject.h"
#include "Engine.h"

// Sets default values
ACollectibleObject::ACollectibleObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("ColliderComponent"));

	RootComponent = ColliderComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));

	MeshComponent->AttachTo(ColliderComponent);
	//AttachTo function is deprecated for this build version, use AttachToComponent
		//MeshComponent->AttachToComponent(ColliderComponent, );

	MovementComponent = CreateDefaultSubobject<UMovementComponent>(TEXT("Movement Component"));

	//Set up a notification for when this component overlaps something
	ColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &ACollectibleObject::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ACollectibleObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectibleObject::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ACollectibleObject::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this))
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::White, FString::Printf(TEXT("Hello World!")));
		Destroy();
		//Set a lifespan to 5 seconds     SetLifeSpan(5);
	}
}


