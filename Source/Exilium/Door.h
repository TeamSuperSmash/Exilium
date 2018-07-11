// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerCharacter.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class EXILIUM_API ADoor : public AInteractable
{
	GENERATED_BODY()
public:
	ADoor();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	bool bActivated = false;
	bool bOpened = false;

	float rotateValue;
	float curveFloatValue;
	float timeLineValue;

	FRotator doorRotation;
	FTimeline doorTimeline;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* DoorFrame;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Door;

	UPROPERTY(EditAnywhere)
		UCurveFloat* DoorCurve;

	UFUNCTION()
		void OpenDoorCheck();

	UFUNCTION()
		void ControlDoor();

	UFUNCTION(BlueprintCallable)
		void ToggleDoor();

	UFUNCTION()
		void SetState();
};
