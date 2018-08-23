// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "Components/PostProcessComponent.h"
#include "PlayerStat.h"
#include "PlayerCharacter.h"
#include "SanityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXILIUM_API USanityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USanityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sanity)
		//ESanityState SanityState;

	APlayerCharacter* player;
	//Post processing 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post processing")
		UPostProcessComponent* postComp;
	//! post process material
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post processing")
		UMaterialInstance* sanityMat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post processing")
		UMaterialInstanceDynamic* sanityDMI;

	//Sanity stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sanity)
		float currentSanity = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float sanityThresholdGap = 30.0f;

	//! sanity counter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sanity)
		float fogCounter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sanity)
		float fogTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sanity)
		float lookTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sanity)
		float lookDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sanity)
		float stayDuration;

	//! player stat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		EPlayerState currentState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		EPlayerState previousState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		ESanityState curSanityState;

	UFUNCTION(BlueprintCallable, Category = Sanity)
		void CheckValidFogState();

	UFUNCTION(BlueprintCallable, Category = Sanity)
		void UpdatePlayerState(float deltaTime);

	UFUNCTION(BlueprintCallable, Category = Sanity)
		void ChangePlayerState(EPlayerState state);

	UFUNCTION(BlueprintCallable, Category = Sanity)
		void UpdateSanity();
};
