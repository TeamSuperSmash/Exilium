
#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class EXILIUM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveForward(float _value);

    void MoveRight(float _value);

    void StartJump();

    void StopJump();

    void StartCrouch();

    void StopCrouch();

    void CrouchImplement(float DeltaTime);

    void StartSprint();

    void StopSprint();

    void StartForward();

    void StopForward();

    void Interact();

    bool bForward;
    bool bCrouching;
    bool bSprinting;

    UPROPERTY(EditAnywhere)
    float currentSpeed = 600.0f;
    UPROPERTY(EditAnywhere)
    float sprintMultiplier = 2.0f;
    UPROPERTY(EditAnywhere)
    float crouchMultiplier = 0.5f;
    UPROPERTY(EditAnywhere)
    float interactionDistance = 200.0f;
    UPROPERTY(EditAnywhere)
    float _baseEyeHeight = 64.0f;
    UPROPERTY(EditAnywhere)
    float _capsuleHeight = 88.0f;

    AActor* FocusedActor = nullptr;
    AActor* FindActorInLOS();
    void CheckFocusActor();
    FCollisionQueryParams TraceParams;

    UPROPERTY(VisibleAnywhere)
        UCameraComponent* FPSCameraComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
        USkeletalMeshComponent* FPSMesh;

    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
        UStaticMeshComponent* CharacterHands;

    UPROPERTY(EditAnywhere)
        TSubclassOf<UCameraShake> WalkShake;

    UPROPERTY(EditAnywhere)
        TSubclassOf<UCameraShake> RunShake;
};
