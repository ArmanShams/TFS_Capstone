// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "Molotov.h"


AMolotov::AMolotov()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sphere collider for the projectile
	//CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollisionComponent"));
	CollisionComponent->InitSphereRadius(SphereRadius);
	CollisionComponent->BodyInstance.SetCollisionProfileName("BlockAll");
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ThisClass::OnComponentHit);
	CollisionComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel5, ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel6, ECR_Ignore);
	//CollisionComponent->SetSimulatePhysics(false);

	// Root Component
	RootComponent = CollisionComponent;

	ConstructorHelpers::FObjectFinder<UStaticMesh>sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	// Mesh Component for the projectile
	//MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	MeshComponent->SetStaticMesh(sphere.Object);
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//MeshComponent->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);

	// ProjectileMovementComponent used to regulate the projectile's movement 
	//ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->UpdatedComponent = RootComponent;
	ProjectileMovementComponent->ProjectileGravityScale = 1.0f;
	//ProjectileMovementComponent->InitialSpeed = InitSpeed;
	//ProjectileMovementComponent->MaxSpeed = 1000.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	//ProjectileMovementComponent->bInitialVelocityInLocalSpace = false;

	// Deconstruct after X seconds as a default
	InitialLifeSpan = LifeTime;
}

void AMolotov::BeginPlay()
{
	Super::BeginPlay();
}

void AMolotov::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMolotov::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);

	Owner = NewOwner;
}

void AMolotov::SetMolotovVelocity(FVector Velocity)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(Velocity);
	ProjectileMovementComponent->MaxSpeed = Velocity.Size();
	ProjectileMovementComponent->InitialSpeed = Velocity.Size();
}

UProjectileMovementComponent* AMolotov::GetProjectileMovementComponent()
{
	return Super::GetProjectileMovementComponent();
}

void AMolotov::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (APawn* RecastedOwner = Cast<APawn>(Owner))
	{
		//UE_LOG(LogTemp, Display, TEXT("Molotov hit a %s"), *OtherActor->GetName());
		UE_LOG(LogTemp, Display, TEXT("Time of Molotov landing: %f, hit a %s"), GetWorld()->GetTimeSeconds(), *OtherActor->GetName());

		if (ACharacter* RecastedOtherCharacter = Cast<ACharacter>(OtherActor))
		{
			UGameplayStatics::ApplyDamage(OtherActor, 10.f, RecastedOwner->GetController(), Owner, TSubclassOf<UDamageType>());
		}
	}
	Destroy();
}