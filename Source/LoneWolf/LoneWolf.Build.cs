// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LoneWolf : ModuleRules
{
	public LoneWolf(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule", "GamePlayTasks", "Slate", "SlateCore", "UMG" });
	}
}
