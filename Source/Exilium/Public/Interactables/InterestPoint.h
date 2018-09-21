// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzlePropsTypeEnum.h"
#include "RoomIDEnum.h"
#include "InterestPoint.generated.h"

UCLASS()
class EXILIUM_API AInterestPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInterestPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private: 
	bool isSettled;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Config)
	ERoomIDEnum roomID;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPuzzlePropsTypeEnum slot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPuzzlePropsTypeEnum item;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector itemLocation;

	UFUNCTION(BlueprintCallable, Category = "Interest point")
	bool CheckMatch();

	/*UFUNCTION(BlueprintCallable, Category = "Interest point")
	void UpdateState();
	UFUNCTION(BlueprintCallable, Category = "Interest point")
	void SetItem(EPuzzlePropsTypeEnum var);*/
	

	
};
