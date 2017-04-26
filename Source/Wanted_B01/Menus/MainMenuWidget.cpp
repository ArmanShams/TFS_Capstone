// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "Wanted_B01/Menus/LWGameUserSettings.h"
#include "MainMenuWidget.h"




void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

float UMainMenuWidget::GetMasterVolume()
{
	return MasterVolume; 
}

float UMainMenuWidget::GetSFXVolume()
{
	return SFXVolume;
}

float UMainMenuWidget::GetMusicVolume()
{
	return MusicVolume;
}

float UMainMenuWidget::GetVoiceVolume()
{
	return VoiceVolume;
}
