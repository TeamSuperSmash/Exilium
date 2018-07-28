// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_Bot_Controller.generated.h"

class UPawnSensingComponent;

/**
 * 
 */
UCLASS()
class EXILIUM_API AAI_Bot_Controller : public AAIController
{
	GENERATED_BODY()
	
public:
	AAI_Bot_Controller();

	virtual void BeginPlay() override;

	virtual void Possess(APawn* Pawn) override;

	virtual void Tick(float DeltaSeconds) override;

	virtual FRotator GetControlRotation() const;

	//Keeps a list of detected player pawns
	UFUNCTION()
		void OnPawnDetected(const TArray<AActor*> &DetectedPawns);

	//Keeps a list of detected noise
	UFUNCTION()
		void OnNoiseHeard(APawn* DetectedPawn, const FVector& Location, float Volume);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightRadius = 500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightAge = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AILoseSightRadius = AISightRadius + 50.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AIFieldOfView = 90.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		bool bIsPlayerDetected = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float DistanceToPlayer = 0.0f;
	
	//Will be obsolete for this project
	//AIPerception component to detect pawns 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		class UAISenseConfig_Sight* SightConfig;
	
	//PawnSensing component to detect pawns
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		UPawnSensingComponent* PawnSensingComponent;
	
};
