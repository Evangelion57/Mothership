// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Mothership427 : ModuleRules
{
	public Mothership427(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
	}
}
