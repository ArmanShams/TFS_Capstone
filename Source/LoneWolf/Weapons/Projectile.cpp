// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sphere collider for the projectile
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollisionComponent"));
	CollisionComponent->InitSphereRadius(SphereRadius);
	//CollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComponent->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
	CollisionComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Ignore);


	// Root Component
	RootComponent = CollisionComponent;

	ConstructorHelpers::FObjectFinder<UStaticMesh>sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	
	// Mesh Component for the projectile
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	MeshComponent->SetStaticMesh(sphere.Object);
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

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);

	Owner = NewOwner;
}

UProjectileMovementComponent* AProjectile::GetProjectileMovementComponent()
{
	if (GetWorld()->HasBegunPlay() && ProjectileMovementComponent != NULL)
	{
		return ProjectileMovementComponent;
	}
	return NULL;
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// OtherComp->AddImpulseAtLocation(GetVelocity() * BulletImpulse, GetActorLocation());
	if (APawn* RecastedOwner = Cast<APawn>(Owner))
	{
		UE_LOG(LogTemp, Display, TEXT("PROJECTILE HIT A THING %s   %s"), *OtherActor->GetName(), *OtherComp->GetName());
		if (ACharacter* RecastedOtherCharacter = Cast<ACharacter>(OtherActor))
		{
			UGameplayStatics::ApplyDamage(OtherActor, Damage, RecastedOwner->GetController(), Owner, TSubclassOf<UDamageType>());
		}
	}
	SetLifeSpan(0.1f);
}