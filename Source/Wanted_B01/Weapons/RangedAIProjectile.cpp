// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "RangedAIProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"


ARangedAIProjectile::ARangedAIProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	// Mesh Component for the projectile
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	// Sphere collider for the projectile
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollisionComponent"));
	CollisionComponent->InitSphereRadius(SphereRadius);
	CollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComponent->OnComponentHit.AddDynamic(this, &ARangedAIProjectile::OnHit);

	// Root Component
	RootComponent = CollisionComponent;

	// ProjectileMovementComponent used to regulate the projectile's movement 
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = InitSpeed;
	ProjectileMovementComponent->MaxSpeed = MaxSpeed;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;

	// Deconstruct after X seconds as a default
	InitialLifeSpan = LifeTime;

	// Disenabling player to walk on it
	// CollisionComponent->SetWalkableSlopeOverride(WalkableSlop_Unwalkable, 0.0f));
	// CollisionComponent->CanCharacterStepUpOn = ECB_No;
}

void ARangedAIProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ARangedAIProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ARangedAIProjectile::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	/*
		// Only add impulse and destroy projectile if we hit a physics
		if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
			Destroy();
		}
	*/
}

