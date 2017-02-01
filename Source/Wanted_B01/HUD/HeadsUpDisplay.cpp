// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "HUDWidget.h"
#include "HeadsUpDisplay.h"

void AHeadsUpDisplay::BeginPlay()
{
	Super::BeginPlay();

	HudWidget = CreateWidget<UHUDWidget>(GetWorld(), HudWidgetClass);
	HudWidget->AddToViewport();
}


