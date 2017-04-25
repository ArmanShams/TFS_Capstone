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

	UFUNCTION(BlueprintCallable, Category = Settings)
	float GetMasterVolume();

	UFUNCTION(BlueprintCallable, Category = Settings)
	float GetSFXVolume();

	UFUNCTION(BlueprintCallable, Category = Settings)
	float GetMusicVolume();

	UFUNCTION(BlueprintCallable, Category = Settings)
	float GetVoiceVolume();

	UPROPERTY(BlueprintReadOnly, Category = Settings)
	float MasterVolume;

	UPROPERTY(BlueprintReadOnly, Category = Settings)
	float SFXVolume;

	UPROPERTY(BlueprintReadOnly, Category = Settings)
	float MusicVolume;

	UPROPERTY(BlueprintReadOnly, Category = Settings)
	float VoiceVolume;

	uint16 ShadowQuality = 0;
	uint16 ShadowMax = 3;

	class LWGameUserSettings* LWGame;
	friend class LWGameUserSettings;

	
	
};
