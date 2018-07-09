// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "FogCube.generated.h"

UCLASS()
class EXILIUM_API AFogCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFogCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class AFogCube* Next;
	UPROPERTY(EditAnywhere)
	class AFogCube* Previous;
	UPROPERTY(EditAnywhere)
	class AFogCube* Left;
	UPROPERTY(EditAnywhere)
	class AFogCube* Right;
	UPROPERTY(EditAnywhere)
	bool isActive;

	UBoxComponent* boxTrigger;

	void RegisterDelegate();
	
};
