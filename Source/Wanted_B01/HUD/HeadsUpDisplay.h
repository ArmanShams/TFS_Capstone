// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "HUDWidget.h"
#include "HeadsUpDisplay.generated.h"


/**
 * 
 */
UCLASS()
class WANTED_B01_API AHeadsUpDisplay : public AHUD
{
	GENERATED_BODY()

public:
	void BeginPlay();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHUDWidget> HudWidgetClass;
	class UHUDWidget* HudWidget;


	
};
