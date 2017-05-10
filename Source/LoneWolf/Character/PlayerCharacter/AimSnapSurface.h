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
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetActive(bool bShouldBeActive);
	virtual void EnableCollision();
	virtual void DisableCollision();
	virtual bool IsBeingOverlapped();
	virtual bool GetIsActive();

	bool bIsOverlapped;
	UPROPERTY(VisibleAnywhere)
	bool bIsEnabled;
protected:
	UPROPERTY(EditInstanceOnly)
	class UBoxComponent* Collider;
	

};
