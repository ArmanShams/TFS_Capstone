// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameUserSettings.h"
#include "LWGameUserSettings.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class WANTED_B01_API ULWGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()
	
public: 
	//Audio
	UPROPERTY(config)
	float MasterVolume;

	UPROPERTY(config)
	float SFXVolume;

	UPROPERTY(config)
	float MusicVolume;

	UPROPERTY(config)
	float VoiceVolume;

public:
	virtual void SetToDefaults() override;
	virtual void ApplySettings(bool bCheckOverrides) override;
	void ApplyAudioSettings();
	bool IsAudioVolumeDirty() const;

protected:
	UPROPERTY(EditAnywhere, Category = SoundClasses)
	USoundClass* MasterSoundClass;

	UPROPERTY(EditAnywhere, Category = SoundClasses)
	USoundClass* SFXSoundClass;

	UPROPERTY(EditAnywhere, Category = SoundClasses)
	USoundClass* MusicSoundClass;

	UPROPERTY(EditAnywhere, Category = SoundClasses)
	USoundClass* VoiceSoundClass;
};
