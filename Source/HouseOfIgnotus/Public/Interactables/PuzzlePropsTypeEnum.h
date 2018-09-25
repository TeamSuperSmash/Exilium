// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PuzzlePropsTypeEnum.generated.h"

UENUM(BlueprintType)
enum class EPuzzlePropsTypeEnum : uint8
{
	NONE	UMETA(DisplayName = "NONE"),
	BRUSH	UMETA(DisplayName = "Brush"),
	SCRAPING_TOOL	UMETA(DisplayName = "ScapingTool"),
	COLOUR_PALETTE  UMETA(DisplayName = "ColourPalette"),
	MUSIC_SHEET		UMETA(DisplayName = "MusicSheet"),
	PIANO_KEY		UMETA(DisplayName = "PianoKey"),
	VINYL			UMETA(DisplayName = "Gramophone"),
	CHESS_PIECE		UMETA(DisplayName = "ChessPiece"),
	GLOBE			UMETA(DisplayName = "Globe"),
	BOOK			UMETA(DisplayName = "Book"),
	_MAX			UMETA(DisplayName = "MaxItemCount")
};
