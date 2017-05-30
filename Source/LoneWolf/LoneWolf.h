// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#ifndef __LoneWolf_H__
#define __LoneWolf_H__

#define ECC_Player ECC_GameTraceChannel1
#define ECC_Enemy ECC_GameTraceChannel4;

#include "Engine.h"

#include "Character/StatusEffects/StatusEffects.h"


#define ECC_Player ECC_GameTraceChannel1;


//DECLARE_LOG_CATEGORY_EXTERN(LogLoneWolf, Log, All);
//DECLARE_LOG_CATEGORY_EXTERN(PlayerControl, Log, All);


#endif

#include "LoneWolf.generated.h"

#pragma once

UENUM(BlueprintType)
namespace UAttackTypes
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

