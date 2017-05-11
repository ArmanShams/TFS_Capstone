// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AimSnapMulti.generated.h"

UCLASS()
class LONEWOLF_API AAimSnapMulti : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAimSnapMulti();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual bool IsAtLeastOneChildOverlapped();
	virtual void SetAllChildrenActive(bool NewState);
	virtual bool AreAllChildernActive();
	virtual bool AreAllChildernInactive();
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	TArray<class AAimSnapSurface*> AimSnapColliders;
	
};
