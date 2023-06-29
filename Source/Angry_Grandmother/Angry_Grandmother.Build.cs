// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Angry_Grandmother : ModuleRules
{
	public Angry_Grandmother(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule","EnhancedInput", "Niagara" });
	    PrivateIncludePaths.AddRange(new string[]{Name});
	}
}
