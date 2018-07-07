// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Components/StaticMeshComponent.h"
#include "Door_Interact.generated.h"

UCLASS()
class EXILIUM_API ADoor_Interact : public AInteractable
{
	GENERATED_BODY()
public:
	ADoor_Interact();
	
protected:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* DoorFrame;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Door;
};
