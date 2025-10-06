// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DigimonWorld : ModuleRules
{
	public DigimonWorld(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
			{ "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "CommonUI", "GameplayTags" });
	}
}