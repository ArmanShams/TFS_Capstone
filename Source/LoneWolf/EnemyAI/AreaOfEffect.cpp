// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "AreaOfEffect.h"
#include "Character/LoneWolfCharacter.h"
#include "Character/PlayerCharacter/CharacterController.h"

// Sets default values
AAreaOfEffect::AAreaOfEffect(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	TimeSinceLastTick = 0.f;

	DamagePerTick = 5.f;

	TicksPerSecond = 2.f;
	LifeTimeInSeconds = 3.f;

	Radius = 30.f;

	TotalTicks = 0;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SphereCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SphereCollider->SetSphereRadius(Radius);

	//sphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AAreaOfEffect::OnBeginOverllap);
}

// Called when the game starts or when spawned
void AAreaOfEffect::BeginPlay()
{
	Super::BeginPlay();

	TimeOfCreation = UGameplayStatics::GetRealTimeSeconds(GetWorld());
}


void AAreaOfEffect::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	TimeSinceLastTick += DeltaTime;
	if ((TimeOfCreation + LifeTimeInSeconds) + TimeSinceLastTick >= UGameplayStatics::GetRealTimeSeconds(GetWorld()))
	{
		if (TimeSinceLastTick >= 1 / TicksPerSecond)
		{
			TArray<AActor*> OverlappedActors;
			SphereCollider->GetOverlappingActors(OverlappedActors, ALoneWolfCharacter::StaticClass());
			if (OverlappedActors.Num() > 0)
			{
				for (size_t i = 0; i < OverlappedActors.Num(); i++)
				{
					UGameplayStatics::ApplyDamage(OverlappedActors[i], DamagePerTick, NULL, this, TSubclassOf<UDamageType>());
				}
			}
			//float realtimeSeconds = UGameplayStatics::GetRealTimeSeconds(GetWorld());
			//UE_LOG(LogTemp, Warning, TEXT("Time since last tick: %f"), timeSinceLastTick);
			//UE_LOG(LogTemp, Warning, TEXT("Total game time: %f"),  realtimeSeconds);
			//UE_LOG(LogTemp, Warning, TEXT("AreaOfEffect ticked!"));

			//STUFF HAPPENS HERE.
			TotalTicks++;

			TimeSinceLastTick = 0.f;

		}
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("AreaOfEffect should now be destroyed! Total ticks: %d"), TotalTicks);
		Destroy();
	}
}
