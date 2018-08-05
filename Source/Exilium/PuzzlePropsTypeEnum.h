// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PuzzlePropsTypeEnum.generated.h"

UENUM(BlueprintType)
enum class EPuzzlePropsTypeEnum : uint8
{
	NONE	UMETA(DisplayName = "NONE"),
	ITEM_1	UMETA(DisplayName = "ITEM_1"),
	_MAX	UMETA(DisplayName = "MAX_ITEM_COUNT")
};
