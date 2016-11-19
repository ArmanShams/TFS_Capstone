// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "Interactable_Health.h"

AInteractable_Health::AInteractable_Health(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	sphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	sphereCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	sphereCollider->SetSphereRadius(10.f);
	RootComponent = sphereCollider;


}

void AInteractable_Health::BeginPlay() {
	Super::BeginPlay();

	if (health == 0)
		health = 10;
}

void AInteractable_Health::Interact(ACharacterController * player) {
	player->ModifyHealth(health);

	Destroy();
}
