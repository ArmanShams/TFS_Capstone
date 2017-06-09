// Fill out your copyright notice in the Description page of Project Settings.

#include "LoneWolf.h"
#include "AimSnapMulti.h"
#include "AimSnapSurface.h"


// Sets default values
AAimSnapMulti::AAimSnapMulti()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAimSnapMulti::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAimSnapMulti::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (IsAtLeastOneChildOverlapped())
	{
		if (!AreAllChildernActive())
		{
			SetAllChildrenActive(true);
			//UE_LOG(LogTemp, Display, TEXT("NOT ALL CHILDREN ARE ACTIVE SO I SET THEM ACTIVE BUT ONLY ONE TIME"));
		}
	}
	else
	{
		if (!AreAllChildernInactive())
		{
			SetAllChildrenActive(false);
			//UE_LOG(LogTemp, Display, TEXT("NOT ALL CHILDREN ARE ACTIVE SO I SET THEM INACTIVE BUT ONLY ONE TIME"));
		}
	}
}

bool AAimSnapMulti::IsAtLeastOneChildOverlapped()
{
	for (size_t i = 0; i < AimSnapColliders.Num(); i++)
	{
		if (AimSnapColliders[i]->IsBeingOverlapped())
		{
			return true;
			break;
		}
	}
	return false;
}

void AAimSnapMulti::SetAllChildrenActive(bool NewState)
{
	for (size_t i = 0; i < AimSnapColliders.Num(); i++)
	{	
		AimSnapColliders[i]->SetActive(NewState);
	}
}

bool AAimSnapMulti::AreAllChildernActive()
{
	for (size_t i = 0; i < AimSnapColliders.Num(); i++)
	{
		if (!AimSnapColliders[i]->GetIsActive())
		{
			return false;
		}
	}
	return true;
}

bool AAimSnapMulti::AreAllChildernInactive()
{
	for (size_t i = 0; i < AimSnapColliders.Num(); i++)
	{
		if (AimSnapColliders[i]->GetIsActive())
		{
			return false;
		}
	}
	return true;
}

