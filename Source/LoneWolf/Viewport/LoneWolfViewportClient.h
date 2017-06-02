// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameViewportClient.h"
#include "LoneWolfViewportClient.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFocusLostSignature);

UCLASS()
class LONEWOLF_API ULoneWolfViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
	
public:
	virtual void LostFocus(FViewport * InViewport) override;

	FFocusLostSignature OnFocusLost;

protected:
	TSubclassOf<class UUserWidget> wPauseHud;
	UUserWidget* PauseHud;
};
