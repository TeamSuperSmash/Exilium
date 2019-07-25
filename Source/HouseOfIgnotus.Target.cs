// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class HouseOfIgnotusTarget : TargetRules
{
	public HouseOfIgnotusTarget(TargetInfo Target) : base(Target)
	{
        bForceEnableExceptions = true; // For Test configuration
        Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "HouseOfIgnotus" } );
	}
}
