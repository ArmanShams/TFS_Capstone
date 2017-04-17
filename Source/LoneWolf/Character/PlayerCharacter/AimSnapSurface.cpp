// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "AimSnapSurface.h"

AAimSnapSurface::AAimSnapSurface()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->AttachTo(RootComponent);
	Collider->RegisterComponent();
	Collider->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Collider->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
	Collider->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	//Collider->SetCollisionProfileName(FName("NoCollision"));
	//FCollisionResponseContainer T = FCollisionResponseContainer(ECollisionResponse::ECR_Overlap);
	//Collider->SetCollisionResponseToChannels(T);
	ECanBeCharacterBase StepUpResponse = ECanBeCharacterBase::ECB_No;
	TEnumAsByte<ECanBeCharacterBase> StepUpResponseByte = StepUpResponse;
	Collider->CanCharacterStepUpOn = StepUpResponseByte;
	Collider->SetCanEverAffectNavigation(false);
	Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);

}

void AAimSnapSurface::BeginPlay()
{
	//Super::BeginPlay();
	
}

// Called every frame
void AAimSnapSurface::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AAimSnapSurface::SetActive(bool bShouldBeActive)
{
	if (bShouldBeActive)
	{
		Collider->SetCollisionResponseToChannel(ECC_GameTraceChannel6, ECollisionResponse::ECR_Block);
		return;
	}
	else
	{
		Collider->SetCollisionResponseToChannel(ECC_GameTraceChannel6, ECollisionResponse::ECR_Ignore);
		return;
	}
}

