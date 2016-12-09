// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractableObjects/Interactable.h"
#include "Interactable_Health.generated.h"

/**
 * 
 */

UCLASS()
class WANTED_B01_API AInteractable_Health : public AInteractable
{
	GENERATED_BODY()

public:

	AInteractable_Health(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere)
	uint8 health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	USphereComponent* sphereCollider;

private:
	virtual void BeginPlay() override;

	virtual void Interact(class ACharacterController* player) override;
	
	
};
