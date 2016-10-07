// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Wanted_B01.h"
#include "Wanted_B01GameMode.h"
#include "Wanted_B01PlayerController.h"
#include "Wanted_B01Character.h"

AWanted_B01GameMode::AWanted_B01GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AWanted_B01PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}