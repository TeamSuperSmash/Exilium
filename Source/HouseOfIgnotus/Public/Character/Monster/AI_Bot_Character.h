// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AI_Bot_Character.generated.h"

UCLASS()
class HOUSEOFIGNOTUS_API AAI_Bot_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAI_Bot_Character();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AWaypoint* NextWaypoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class AAI_Bot_Controller* MyController;


		class UCharacterMovementComponent* MovementComponent;

	//Function declared in c++ but defined inside blueprint
	UFUNCTION(BlueprintImplementableEvent, Category = CustomStuff)
		void QTEStart(int currState );

	UFUNCTION(BlueprintImplementableEvent, Category = CustomStuff)
		void SetMaxAcceleration(float setSpeed);

	UFUNCTION(BlueprintImplementableEvent, Category = CustomStuff)
		void CheckRendered();

	UFUNCTION(BlueprintCallable, Category = CustomStuff)
		void EventFailQTE();

	UFUNCTION(BlueprintCallable, Category = CustomStuff)
		void HeartbeatSuccess();



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CustomStuff)
		bool bIsPlayerDetected = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
