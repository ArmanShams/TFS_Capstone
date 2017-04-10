// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "KegProjectile.h"


// Sets default values
AKegProjectile::AKegProjectile()
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
	ProjectileMovementComponent->ProjectileGravityScale = 1.f;
	ProjectileMovementComponent->InitialSpeed = InitSpeed;
	ProjectileMovementComponent->MaxSpeed = MaxSpeed;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bIsSliding = true;

	// Deconstruct after X seconds as a default
	InitialLifeSpan = LifeTime;
}

// Called when the game starts or when spawned
void AKegProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKegProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AKegProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::White, FString::Printf(TEXT("Projectile hit something")));
	UE_LOG(LogTemp, Display, TEXT("KEG HIT A THING %s"), *OtherActor->GetName());
	// OtherComp->AddImpulseAtLocation(GetVelocity() * BulletImpulse, GetActorLocation());
	UGameplayStatics::ApplyDamage(OtherActor, Damage, GetWorld()->GetFirstPlayerController(), this, TSubclassOf<UDamageType>());

	//if (Cast<class ACharacterController>(WeaponSpawnedThis->OwnerCharacter))
	//{
	//	UE_LOG(LogTemp, Display, TEXT("Owned by a player"));
	//}
	//

	Destroy();
}

