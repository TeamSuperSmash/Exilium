// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RoomFogStateEnum.generated.h"

UENUM(BlueprintType)
enum class ERoomFogStateEnum : uint8
{
	NONE	UMETA(DisplayName = "NONE"),
	STAGE_1 UMETA(DisplayName = "STAGE_ONE"),
	STAGE_2 UMETA(DisplayName = "STAGE_ONE"),
	STAGE_3 UMETA(DisplayName = "STAGE_ONE"),
	_MAX    UMETA(DisplayName = "TOTAL_STATE")
};

