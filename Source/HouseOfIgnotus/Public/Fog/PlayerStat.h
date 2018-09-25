// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerStat.generated.h"

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	NONE	UMETA(DisplayName = "NONE"),
	INFOG	UMETA(DisplayName = "INFOG"),
	LOOKATMONSTER	UMETA(DisplayName = "LOOKATMONSTER"),
	BREATHINGMINI	UMETA(DisplayName = "BREATHINGMINI"),
	HEARTBEATMINI	UMETA(DisplayName = "HEARTBEATMINI")
};
