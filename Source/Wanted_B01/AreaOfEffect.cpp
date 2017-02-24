// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "AreaOfEffect.h"
#include "Character/CharacterController.h"

// Sets default values
AAreaOfEffect::AAreaOfEffect(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	timeSinceLastTick = 0.f;

	damagePerTick = 5;

	ticksPerSecond = 2.f;
	lifeTimeInSeconds = 3.f;

	radius = 30.f;

	totalTicks = 0;

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


void AAreaOfEffect::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	timeSinceLastTick += DeltaTime;
	if ((timeOfCreation + lifeTimeInSeconds) + timeSinceLastTick >= UGameplayStatics::GetRealTimeSeconds(GetWorld()))
	{
		if (timeSinceLastTick >= 1 / ticksPerSecond)
		{
			if (sphereCollider->IsOverlappingActor(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
			{
				ACharacterController* player = Cast<ACharacterController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
				player->ModifyHealth(-damagePerTick);

				//UE_LOG(LogTemp, Warning, TEXT("Overlapping another actor"));
			}
			//float realtimeSeconds = UGameplayStatics::GetRealTimeSeconds(GetWorld());
			//UE_LOG(LogTemp, Warning, TEXT("Time since last tick: %f"), timeSinceLastTick);
			//UE_LOG(LogTemp, Warning, TEXT("Total game time: %f"),  realtimeSeconds);
			UE_LOG(LogTemp, Warning, TEXT("AreaOfEffect ticked!"));

			//STUFF HAPPENS HERE.
			totalTicks++;

			timeSinceLastTick = 0.f;

		}
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("AreaOfEffect should now be destroyed! Total ticks: %d"), totalTicks);
		Destroy();
	}
}
