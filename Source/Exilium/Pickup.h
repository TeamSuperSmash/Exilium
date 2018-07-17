// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "PlayerCharacter.h"
#include "Pickup.generated.h"

UCLASS()
class EXILIUM_API APickup : public AActor, public IInteractable
{
	GENERATED_BODY()
public:
	APickup();

	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ItemID;

	UPROPERTY(EditAnywhere)
		bool bSimulatePhysics = true;

	UPROPERTY(EditAnywhere)
		bool bEnableGravity = true;

	UPROPERTY(EditAnywhere)
		float linearDamping = 0.01f;

	UPROPERTY(EditAnywhere)
		float angularDamping = 0.0f;

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteract();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Interactable)
	bool Interact();
	virtual bool Interact_Implementation();

	UFUNCTION(BlueprintCallable, Category = Pickup)
	FString GetUseText() const;

public:
	UPROPERTY(EditAnywhere, Category = Pickup)
	FString Name;

	UPROPERTY(EditAnywhere, Category = Pickup)
	FString Action;
};
