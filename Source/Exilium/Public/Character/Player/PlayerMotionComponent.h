//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "Components/ActorComponent.h"
//
////UE4 Classes
////#include "GameFramework/Pawn.h"
//
////Native Classes
//#include "PlayerCharacter.h"
//#include "Components/CapsuleComponent.h"
//#include "Camera/CameraComponent.h"
//
////Utilities
//#include "Vector2D.h"
//
////Enums
//#include "PlayerMotionState.h"
//
//#include "PlayerMotionComponent.generated.h"
//
//UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
//class EXILIUM_API UPlayerMotionComponent : public UActorComponent
//{
//	GENERATED_BODY()
//
//public:
//	APlayerCharacter* pawn;
//	UCameraComponent* camera;
//	UCapsuleComponent* capsuleCol;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	EPlayerMotionState motionState;
//
//	//Config
//	//==========
//	//	Crouch
//	//==========
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
//	float currentEyeHeight;
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
//	float currentColliderHeight;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
//	float baseEyeHeight;
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
//	float baseColliderHeight;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float crouchedEyeHeight;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float crouchedColliderHeight;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	float crouchSpeed;
//
//
////==================================================
//
//public:	
//	// Sets default values for this component's properties
//	UPlayerMotionComponent();
//
//protected:
//	// Called when the game starts
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
//
//		
//public:
//	void Move(FVector2D value);
//	void OnCrouch(float deltaTime);
//};
