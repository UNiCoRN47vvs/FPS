// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using UnrealBuildTool.Rules;

public class FPS : ModuleRules
{
	public FPS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
 
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "Slate", "SlateCore", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "MetasoundEngine", "UMG",
															"AIModule", "NavigationSystem", "Niagara", "GameplayTags" });
	}
}
