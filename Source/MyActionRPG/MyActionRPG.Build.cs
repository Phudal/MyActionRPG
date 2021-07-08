// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyActionRPG : ModuleRules
{
	public MyActionRPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core", "CoreUObject", "Engine", "InputCore", "AIModule", "NavigationSystem", "GamePlayTasks",
			"UMG", "Slate", "SlateCore", "Json", "JsonUtilities", "HeadMountedDisplay"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });

		PrivateIncludePaths.Add(ModuleDirectory);
		PublicIncludePaths.Add(ModuleDirectory);
	}
}
