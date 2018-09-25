// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerMotionState.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPlayerMotionState : uint8
{
	Idle			UMETA(DisplayName = "Idle"),
	Walking			UMETA(DisplayName = "Walking"),
	Sprinting		UMETA(DisplayName = "Sprinting"),
	Crouching		UMETA(DisplayName = "Crouching")
};
