// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "AreaOfEffect.h"


// Sets default values
AAreaOfEffect::AAreaOfEffect(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	timeSinceLastTick = 0.f;


	ticksPerSecond = 3.f;
	lifeTimeInSeconds = 3.f;

	radius = 30.f;

	sphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	sphereCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	sphereCollider->SetSphereRadius(radius);

	//sphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AAreaOfEffect::OnBeginOverllap);
}

// Called when the game starts or when spawned
void AAreaOfEffect::BeginPlay()
{
	Super::BeginPlay();

	timeOfCreation = UGameplayStatics::GetRealTimeSeconds(GetWorld());
}

// Called every frame
void AAreaOfEffect::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	timeSinceLastTick += DeltaTime;

	if ((timeOfCreation + lifeTimeInSeconds) >= UGameplayStatics::GetRealTimeSeconds(GetWorld()))
	{
		if (timeSinceLastTick >= ticksPerSecond / 10)
		{
			//float realtimeSeconds = UGameplayStatics::GetRealTimeSeconds(GetWorld());
			//UE_LOG(LogTemp, Warning, TEXT("Time since last tick: %f"), timeSinceLastTick);
			//UE_LOG(LogTemp, Warning, TEXT("Total game time: %f"),  realtimeSeconds);

			UE_LOG(LogTemp, Warning, TEXT("AreaOfEffect ticked!"));

			//STUFF HAPPENS HERE.

			timeSinceLastTick = 0.f;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AreaOfEffect should now be destroyed!"));
		Destroy();
	}
}
