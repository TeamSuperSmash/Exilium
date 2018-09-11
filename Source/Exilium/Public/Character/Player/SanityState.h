// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SanityState.generated.h"

UENUM(BlueprintType)
enum class ESanityState : uint8
{
	SANITY_LEVEL_0		UMETA(DisplayName = "SANITY_LEVEL_0"),
	SANITY_LEVEL_1		UMETA(DisplayName = "SANITY_LEVEL_1"),
	SANITY_LEVEL_2		UMETA(DisplayName = "SANITY_LEVEL_2"),
	SANITY_LEVEL_3		UMETA(DisplayName = "SANITY_LEVEL_3"),
	SANITY_LEVEL_4		UMETA(DisplayName = "SANITY_LEVEL_4")
};
