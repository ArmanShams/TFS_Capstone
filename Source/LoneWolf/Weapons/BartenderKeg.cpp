// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "BartenderKeg.h"
#include "Character/LoneWolfCharacter.h"

ABartenderKeg::ABartenderKeg()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleHalfHeight = 20.f;
	CapsuleRadius = 10.f;

	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	//CollisionComponent->InitSphereRadius(SphereRadius);
	CollisionComponent->SetCapsuleHalfHeight(CapsuleHalfHeight);
	CollisionComponent->SetCapsuleRadius(CapsuleRadius);
	CollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Ignore);

	// Root Component
	RootComponent = CollisionComponent;

	Collider = CollisionComponent;

	//ConstructorHelpers::FObjectFinder<UStaticMesh>sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	// Mesh Component for the projectile
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	//MeshComponent->SetStaticMesh(sphere.Object);
	MeshComponent->SetupAttachment(RootComponent);


	// ProjectileMovementComponent used to regulate the projectile's movement 
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->UpdatedComponent = RootComponent;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	ProjectileMovementComponent->InitialSpeed = InitSpeed;
	ProjectileMovementComponent->MaxSpeed = MaxSpeed;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;

	// Deconstruct after X seconds as a default
	InitialLifeSpan = LifeTime;

	
}

void ABartenderKeg::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentHit.AddDynamic(this, &ThisClass::OnComponentHit);

}

void ABartenderKeg::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABartenderKeg::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);

	Owner = NewOwner;
}

UProjectileMovementComponent* ABartenderKeg::GetProjectileMovementComponent()
{
	if (GetWorld()->HasBegunPlay() && ProjectileMovementComponent != NULL)
	{
		return ProjectileMovementComponent;
	}
	return NULL;
}

void ABartenderKeg::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ALoneWolfCharacter* RecastActor = Cast<ALoneWolfCharacter>(OtherActor))
	{
		
	}
}

