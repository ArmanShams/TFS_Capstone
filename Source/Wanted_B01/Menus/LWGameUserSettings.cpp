// Fill out your copyright notice in the Description page of Project Settings.

#include "Wanted_B01.h"
#include "LWGameUserSettings.h"
#include "AudioDevice.h"

void ULWGameUserSettings::SetToDefaults()
{
	Super::SetToDefaults();
	
	MasterVolume = 1.f;
	MusicVolume = 1.f;
	SFXVolume = 1.f;
	VoiceVolume = 1.f;
}

void ULWGameUserSettings::ApplySettings(bool bCheckOverrides)
{
	Super::ApplySettings(bCheckOverrides);

	ApplyAudioSettings();
}

void ULWGameUserSettings::ApplyAudioSettings()
{
	if (MasterSoundClass)
	{
		MasterSoundClass->Properties.Volume = MasterVolume;
	}
	if (SFXSoundClass)
	{
		SFXSoundClass->Properties.Volume = SFXVolume;
	}
	if (MusicSoundClass)
	{
		MusicSoundClass->Properties.Volume = MusicVolume;
	}
	if (VoiceSoundClass)
	{
		VoiceSoundClass->Properties.Volume = VoiceVolume;
	}
}

bool ULWGameUserSettings::IsAudioVolumeDirty() const
{
	if (MasterSoundClass && MasterSoundClass->Properties.Volume != MasterVolume)
	{
		return true;
	}

	if (SFXSoundClass && SFXSoundClass->Properties.Volume != SFXVolume)
	{
		return true;
	}

	if (MusicSoundClass && MusicSoundClass->Properties.Volume != MusicVolume)
	{
		return true;
	}

	if (VoiceSoundClass && VoiceSoundClass->Properties.Volume != VoiceVolume)
	{
		return true;
	}

	return false;
}
