// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Citadel_GameTarget : TargetRules
{
	public Citadel_GameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Citadel_Game" } );
    }
}
