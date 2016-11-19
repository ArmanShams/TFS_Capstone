// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "Interactable_Torch.h"

AInteractable_Torch::AInteractable_Torch(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	sphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	sphereCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	sphereCollider->SetSphereRadius(10.f);
	RootComponent = sphereCollider;

}


void AInteractable_Torch::BeginPlay() {
	Super::BeginPlay();

}

void AInteractable_Torch::Interact(ACharacterController * player) {
	//MEANS OF UPDATING PROGRESS WILL BE ADDED ONCE GAME MANAGER IS IMPLEMENTED

	Destroy();
}

