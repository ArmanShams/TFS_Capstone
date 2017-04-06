// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#ifndef __WANTED_B01_H__
#define __WANTED_B01_H__

#define ECC_Interactable ECC_GameTraceChannel1

#include "Engine.h"


#define ECC_Interactable ECC_GameTraceChannel1;


//DECLARE_LOG_CATEGORY_EXTERN(LogWanted_B01, Log, All);
//DECLARE_LOG_CATEGORY_EXTERN(PlayerControl, Log, All);


#endif

#include "Wanted_B01.generated.h"

#pragma once
UENUM(BlueprintType)
namespace AttackTypes
{
	enum MeleeAttackType
	{
		NONE			UMETA(DisplayName = "None"),
		SWIFT			UMETA(DisplayName = "Swift attack"),
		LIGHT			UMETA(DisplayName = "Light attack"),
		HEAVY			UMETA(DisplayName = "Heavy attack")
	};
}
UENUM(BlueprintType)
namespace CharacterState
{
	
	enum StatusEffect
	{
		NONE			UMETA(DisplayName = "None"),
		SNARE			UMETA(DisplayName = "Snared"),
		STUN			UMETA(DisplayName = "Stunned"),
		KNOCKDOWN		UMETA(DisplayName = "KnockedDown"),
		INTERRUPTABLE	UMETA(DisplayName = "Interruptable"),
		UNSTOPPABLE		UMETA(DisplayName = "Unstoppable"),
		INVULNERABLE	UMETA(DisplayName = "Invulnerable")
	};
}

