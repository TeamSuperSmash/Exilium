// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "PlayerStat.generated.h"

/**
 * 
 */
UCLASS()
class EXILIUM_API UPlayerStat : public UUserDefinedStruct
{
	GENERATED_BODY()

	USTRUCT(BlueprintType)
	struct BoolVar;
};
