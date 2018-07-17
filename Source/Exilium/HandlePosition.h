// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HandlePosition.generated.h"

UENUM(BlueprintType)
enum class EHandlePosition : uint8
{
	HP_Center				UMETA(DisplayName = "Center"),
	HP_Top					UMETA(DisplayName = "Top"),
	HP_Bottom				UMETA(DisplayName = "Bottom"),
	HP_RotatedVertically	UMETA(DisplayName = "RotatedVertically"),
	HP_RotatedSideways		UMETA(DisplayName = "RotatedSideways"),
	HP_Total				UMETA(DisplayName = "Total")
};
