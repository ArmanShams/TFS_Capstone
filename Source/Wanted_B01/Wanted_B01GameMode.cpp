// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Wanted_B01.h"
#include "Wanted_B01GameMode.h"

AWanted_B01GameMode::AWanted_B01GameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// TEXT("AssetPath'/MyAsset.MyAsset_C'") to get the class. <APawn>
	ConstructorHelpers::FClassFinder<APawn> CharacterClassAsset(TEXT("Blueprint'/Game/TopDownCPP/Blueprints/CharacterControllerBlueprint.CharacterControllerBlueprint_C'"));
	if (CharacterClassAsset.Class)
	{
		DefaultPawnClass = CharacterClassAsset.Class;
	}

}

