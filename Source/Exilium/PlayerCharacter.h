
#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/AudioComponent.h"
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

    void HoldLighter();

    void HoldCandle();

    void HoldMusicBox();

    void HoldBareHand();

    void ActivateItem();

    void DeActivateItem();

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
    UPROPERTY(EditAnywhere)
        float lighterIntensity = 1000.0f;
    UPROPERTY(EditAnywhere)
        float candleIntensity = 3000.0f;
    UPROPERTY(EditAnywhere)
        int itemType = 0;

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

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Light)
        UPointLightComponent* PlayerLight;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Sound)
        UAudioComponent* PlayerSound;

    UPROPERTY(EditAnywhere)
        TSubclassOf<UCameraShake> IdleShake;

    UPROPERTY(EditAnywhere)
        TSubclassOf<UCameraShake> WalkShake;

    UPROPERTY(EditAnywhere)
        TSubclassOf<UCameraShake> RunShake;
};
