
#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
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

    void StartSprint();

    void StopSprint();

    void StartForward();

    void StopForward();

    bool bForward;
    bool bCrouching;
    bool bSprinting;
    float currentSpeed;
    float sprintMultiplier = 2.0f;
    float interactionDistance = 200.0f;

    AActor* FocusedActor = nullptr;
    AActor* FindActorInLOS();
    FCollisionQueryParams TraceParams;

    UPROPERTY(VisibleAnywhere)
        UCameraComponent* FPSCameraComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
        USkeletalMeshComponent* FPSMesh;
};
