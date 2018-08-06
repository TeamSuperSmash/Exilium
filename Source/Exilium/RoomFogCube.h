// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FogCube.h"
#include "RoomFogStateEnum.h"
#include "RoomFogCube.generated.h"

/**
 * 
 */
UCLASS()
class EXILIUM_API ARoomFogCube : public AFogCube
{
	GENERATED_BODY()
/*public:
	// Sets default values for this actor's properties
	ARoomFogCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;*/
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERoomFogStateEnum curState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float couplingRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isNormalized;

	UFUNCTION(BlueprintCallable, Category = "Fog")
	void UpdateFogState();
};
