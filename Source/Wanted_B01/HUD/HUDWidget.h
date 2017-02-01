// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_B01_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	

public: 
	virtual void NativeConstruct() override;
	
protected: 

	// Requires a widget by the name of the variable name.
	UPROPERTY(meta = (BindWidget))
	UImage* BackgroundWidget;
	
	// Optional binding, not required, will not break a build if no widget is present.
	UPROPERTY(meta = (BindWidgetOptional))
	UImage* OptionalBackgroundWidget;

};
