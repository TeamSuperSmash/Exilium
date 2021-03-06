// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FogCube.h"
#include "InterestPoint.h"
#include "RoomFogStateEnum.h"
#include "RoomIDEnum.h"
#include "RoomFogCube.generated.h"

/**
 * 
 */
UCLASS()
class HOUSEOFIGNOTUS_API ARoomFogCube : public AFogCube
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)
	ERoomIDEnum roomID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERoomFogStateEnum curState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float couplingRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isNormalized;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AInterestPoint*> puzzleList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int debugCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float timer;

	/*UFUNCTION(BlueprintCallable, Category = "Fog")
	void CheckPuzzleProgress();*/
	UFUNCTION(BlueprintCallable, Category = "Fog")
	void UpdateFogState();
	UFUNCTION(BlueprintCallable, Category = "Fog")
	void SetCouplingRate(float duration, float targetRate, float currentRate, float deltaTime);

};
