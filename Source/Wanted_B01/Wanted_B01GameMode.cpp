// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Wanted_B01.h"
#include "Wanted_B01GameMode.h"

AWanted_B01GameMode::AWanted_B01GameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// TEXT("AssetPath'/MyAsset.MyAsset_C'") to get the class. <APawn>
	ConstructorHelpers::FClassFinder<APawn> CharacterClassAsset(TEXT("Blueprint'/Game/Blueprints/Player/CharacterControllerBlueprint.CharacterControllerBlueprint_C'"));
	if (CharacterClassAsset.Class)
	{
		DefaultPawnClass = CharacterClassAsset.Class;
	}
	
	//ConstructorHelpers::FClassFinder<UUserWidget>HUDAsset(TEXT("WidgetBlueprint'/Game/Blueprints/Player/HUD.HUD_C'"));
	//if (HUDAsset.Class)
	//{
	//	HUDClass = HUDAsset.Class;
	//}
	// 

}