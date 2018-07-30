// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI_Bot_Controller.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	MS_CHASE	UMETA(DisplayName = "Chase"),
	MS_ALERT	UMETA(DisplayName = "Alert"),
	MS_ROAM		UMETA(DisplayName = "Roam"),
};

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



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AAI_Bot_Character* MyCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class APlayerCharacter* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		EMonsterState MonsterState;

	UFUNCTION(BlueprintCallable, Category = AI)
		void FindPrey();

	UFUNCTION(BlueprintCallable, Category = AI)
		void FindPath();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		FVector NavTarget; 

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AIMovePause = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		bool AICanMove = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		bool QTEStarted = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		bool IsBeingSeen = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float SeenDuration;





	//Keeps a list of detected player pawns
	UFUNCTION()
		void OnPawnDetected(const TArray<AActor*> &DetectedPawns);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightRadius = 500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AISightAge = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AILoseSightRadius = AISightRadius + 50.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AIFieldOfView = 90.0f;


	//PawnSensing component to detect pawns
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		UPawnSensingComponent* PawnSensingComponent;

	//Keeps a list of detected noise
	UFUNCTION()
		void OnNoiseHeard(APawn* DetectedPawn, const FVector& Location, float Volume);

	UFUNCTION(BlueprintCallable, Category = AI)
		void SetMonsterState(int newState);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float RoamSpeed = 50.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AlertSpeed = 85.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float ChaseSpeed = 125.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float ChaseDuration;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float AlertDetectionRadius = 850.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float BreathingDetectionRadius = 500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float SpecialDetectionRadius = 1250.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float CurrDetectionRadius;

	FVector GetNextPathPoint(FVector DestPos);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	FVector NextPathPoint;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		bool bIsPlayerDetected = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float DistanceToPlayer = 0.0f;
	
	//Will be obsolete for this project
	//AIPerception component to detect pawns 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		class UAISenseConfig_Sight* SightConfig;
	
	
	
};
