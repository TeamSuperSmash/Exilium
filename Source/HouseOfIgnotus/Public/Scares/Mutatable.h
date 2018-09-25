// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Mutatable.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UMutatable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HOUSEOFIGNOTUS_API IMutatable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Mutatable)
	bool Mutate();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Mutatable)
	bool Demutate();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Mutatable)
	bool GetMutationCondition();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Mutatable)
	bool MutationConditionOverridesManager();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Mutatable)
	bool GetDemutationCondition();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Mutatable)
	bool DemutationConditionOverridesManager();
};
