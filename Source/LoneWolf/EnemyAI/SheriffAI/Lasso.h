// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CableComponent.h"
#include "Lasso.generated.h"

UCLASS()
class LONEWOLF_API ALasso : public AActor
{
	GENERATED_BODY()

public:
	ALasso();

	UPROPERTY(EditAnywhere)
	class UCableComponent* CableComponent;
};
