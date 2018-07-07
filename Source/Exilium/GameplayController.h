// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacter.h"
#include "GameplayController.generated.h"

UCLASS()
class EXILIUM_API AGameplayController : public APlayerController
{
	GENERATED_BODY()
public:
	// The interactable the player is currently looking at. 
	// Will be nullptr if player is not looking at usable.
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class AInteractable* CurrentInteractable;

	UFUNCTION(BlueprintCallable, Category = "Utils")
		void AddItemToInventoryByID(FName ID);

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		TArray<FInventoryItem> Inventory;

protected:
	void Interact();

	virtual void SetupInputComponent() override;
};
