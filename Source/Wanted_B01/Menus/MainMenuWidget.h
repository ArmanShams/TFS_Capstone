// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class WANTED_B01_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Options")
	float GetMasterVolume();

	UFUNCTION(BlueprintCallable, Category = "Options")
	float GetSFXVolume();

	UFUNCTION(BlueprintCallable, Category = "Options")
	float GetMusicVolume();

	UFUNCTION(BlueprintCallable, Category = "Options")
	float GetVoiceVolume();

	UPROPERTY(BlueprintReadOnly, Category = "Options")
	float MasterVolume;

	UPROPERTY(BlueprintReadOnly, Category = "Options")
	float SFXVolume;

	UPROPERTY(BlueprintReadOnly, Category = "Options")
	float MusicVolume;

	UPROPERTY(BlueprintReadOnly, Category = "Options")
	float VoiceVolume;

	friend class LWGameUserSettings;

	
	
};
