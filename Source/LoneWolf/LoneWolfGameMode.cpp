// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "LoneWolf.h"
#include "LoneWolfGameMode.h"

ALoneWolfGameMode::ALoneWolfGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// TEXT("AssetPath'/MyAsset.MyAsset_C'") to get the class. <APawn>
	ConstructorHelpers::FClassFinder<APawn> CharacterClassAsset(TEXT("Blueprint'/Game/Blueprints/Player/CharacterControllerBlueprint.CharacterControllerBlueprint_C'"));
	if (CharacterClassAsset.Class)
	{
		DefaultPawnClass = CharacterClassAsset.Class;
	}

}

