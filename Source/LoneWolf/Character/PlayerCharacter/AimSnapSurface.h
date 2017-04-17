// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AimSnapSurface.generated.h"

UCLASS()
class LONEWOLF_API AAimSnapSurface : public AActor
{
	GENERATED_BODY()
	
public:	
	AAimSnapSurface();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void SetActive(bool bShouldBeActive);

protected:
	UPROPERTY(EditInstanceOnly)
	class UBoxComponent* Collider;
	
	//bool bIsActive
};
