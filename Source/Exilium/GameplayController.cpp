// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayController.h"
#include "Exilium.h"
#include "Interactable.h"
#include "GameplayGameMode.h"
#include "PlayerCharacter.h"

void AGameplayController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("InteractKey", IE_Pressed, this, &AGameplayController::Interact);
}

void AGameplayController::Interact()
{
	if (CurrentInteractable)
	{
		CurrentInteractable->Interact(this);
	}
}

void AGameplayController::AddItemToInventoryByID(FName ID)
{
	AGameplayGameMode* GameMode = Cast<AGameplayGameMode>(GetWorld()->GetAuthGameMode());
	UDataTable* ItemTable = GameMode->GetItemDB();

	FInventoryItem* ItemToAdd = ItemTable->FindRow<FInventoryItem>(ID, "");

	if (ItemToAdd)
	{
		Inventory.Add(*ItemToAdd);
	}
}


