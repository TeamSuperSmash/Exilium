// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS()
class EXILIUM_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractable();

	virtual void BeginPlay() override;

	//Function that is called when player interacts with interactable.
	//Marked as BlueprintImplementableEvent so designers can set custom functions.
	UFUNCTION(BlueprintImplementableEvent)
		void Interact(APlayerController* Controller);

	UPROPERTY(EditDefaultsOnly)
		FString Name;

	UPROPERTY(EditDefaultsOnly)
		FString Action;

	UFUNCTION(BlueprintCallable, Category = "Pickup")
		FString GetUseText() const { return FString::Printf(TEXT("%s : Press F To %s"), *Name, *Action); }
};
