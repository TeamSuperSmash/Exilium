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
	class AFogCube* next;
	UPROPERTY(EditAnywhere)
	class AFogCube* previous;
	UPROPERTY(EditAnywhere)
	class AFogCube* left;
	UPROPERTY(EditAnywhere)
	class AFogCube* right;
	UPROPERTY(EditAnywhere)
	bool isActive;

	UFUNCTION(BlueprintCallable, Category = "Fog")
	void SetActive(bool value);

	UFUNCTION(BlueprintCallable, Category = "Fog")
	void Spread();
};
