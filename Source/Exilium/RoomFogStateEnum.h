// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RoomFogStateEnum.generated.h"

UENUM(BlueprintType)
enum class ERoomFogStateEnum : uint8
{
	NONE	UMETA(DisplayName = "NONE"),
	DENSE UMETA(DisplayName = "Dense"),
	MEDIUM UMETA(DisplayName = "Medium"),
	LESS UMETA(DisplayName = "Less"),
	_MAX    UMETA(DisplayName = "TOTAL_STATE")
};

