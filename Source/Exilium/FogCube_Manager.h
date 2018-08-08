// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FogCube.h"
#include "RoomFogCube.h"
#include "FogCube_Manager.generated.h"

UCLASS()
class EXILIUM_API AFogCube_Manager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFogCube_Manager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AFogCube* current;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ARoomFogCube*> fogRoomList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isCompleted;

	UFUNCTION(BlueprintCallable, Category = "FogManager")
	void CheckCurrent(AFogCube* cube);
	UFUNCTION(BlueprintCallable, Category = "FogManager")
	void CheckProgress();
	 
};
