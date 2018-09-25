// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Components/SceneComponent.h"
#include "Components/TimelineComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Pawn.h"
#include "HandlePosition.h"
#include "WeirdDoor.generated.h"

UCLASS(Abstract, Blueprintable)
class HOUSEOFIGNOTUS_API AWeirdDoor : public AActor, public IInteractable
{
	GENERATED_BODY()

private:
	USceneComponent* m_rotator;
	USceneComponent* m_rotator_bottom;
	USceneComponent* m_rotator_center;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = DoorSettings)
	bool isOpened;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = DoorSettings)
	bool isReady;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = DoorSettings)
	float rotateDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DoorSettings)
	EHandlePosition handlePosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DoorSettings)
	UCurveFloat* animationCurve;

	FTimeline doorTimeline;

public:	
	// Sets default values for this actor's properties
	AWeirdDoor();

protected:
	virtual void PostInitializeComponents() override;

	// Called before BeginPlay()
	UFUNCTION(BlueprintImplementableEvent)
	void Awake();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	/**
	 * Initialize components
	 */
	UFUNCTION(BlueprintCallable, Category = Door)
	void InitializeComponents(USceneComponent* rotator, USceneComponent* rotator_bottom, USceneComponent* rotator_center);

	// Getters
	UFUNCTION(BlueprintPure, Category = Door)
	USceneComponent* GetRotator();

	UFUNCTION(BlueprintPure, Category = Door)
	USceneComponent* GetRotatorBottom();

	UFUNCTION(BlueprintPure, Category = Door)
	USceneComponent* GetRotatorCenter();

	UFUNCTION()
	void ControlDoor();
	
	UFUNCTION()
	void SetState();

	/**
	 * Open / Close the door
	 * @params rotator Rotate root of the door
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Interactable)
	bool Interact();
	virtual bool Interact_Implementation();

	UFUNCTION(BlueprintImplementableEvent)
	void OnInteract();

	UFUNCTION(BlueprintCallable, Category = Door)
	void Debug_ChangeDoorHandlePosition();

};
