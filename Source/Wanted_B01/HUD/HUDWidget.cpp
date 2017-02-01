// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "HUDWidget.h"


void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (BackgroundWidget)
	{
		UE_LOG(LogTemp, Display, TEXT("WE ARE IN THE BEAM"));

	}
}

