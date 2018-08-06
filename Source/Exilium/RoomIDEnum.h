// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RoomIDEnum.generated.h"

UENUM(BlueprintType)
enum class ERoomIDEnum : uint8
{
	NONE	UMETA(DisplayName = "NONE"),
	MUSIC	UMETA(DisplayName = "MusicRoom"),
	STUDY	UMETA(DisplayName = "StudyRoom"),
	DRAWING	UMETA(DisplayName = "DrawingRoom"),
	_MAX	UMETA(DisplayName = "MaxRoomCount")
};
