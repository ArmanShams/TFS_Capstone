// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CollectibleObject.generated.h"


UCLASS()
class LONEWOLF_API ACollectibleObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectibleObject();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
private:

	UPROPERTY(EditDefaultsOnly)
		USphereComponent* ColliderComponent;

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* CollectibleMesh;

	UPROPERTY(EditDefaultsOnly)
		UMovementComponent* MovementComponent;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


};
