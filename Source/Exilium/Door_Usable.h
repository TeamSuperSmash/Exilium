
#pragma once

#include "CoreMinimal.h"
#include "Components/MeshComponent.h"
#include "Interact_Interface.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Door_Usable.generated.h"

UCLASS()
class EXILIUM_API ADoor_Usable : public AActor, public IInteract_Interface
{
	GENERATED_BODY()
	
public:	
	ADoor_Usable();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

#pragma region GlobalObjectVariables
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void OnInteract(AActor* Caller);
    virtual void OnInteract_Implementation(AActor* Caller) override;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void StartFocus();
    virtual void StartFocus_Implementation() override;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void EndFocus();
    virtual void EndFocus_Implementation() override;
#pragma endregion

#pragma region IndividualObjectVariables
    void OpenDoorCheck();

    bool bActivated = false;
    bool bOpened = false;

    float rotateValue;
    float curveFloatValue;
    float timeLineValue;

    FRotator doorRotation;
    FTimeline doorTimeline;

    UPROPERTY(EditAnywhere)
        UStaticMeshComponent* DoorFrame;

    UPROPERTY(EditAnywhere)
        UStaticMeshComponent* Door;

    UPROPERTY(EditAnywhere)
        UCurveFloat* DoorCurve;

    UFUNCTION()
        void ControlDoor();

    UFUNCTION()
        void ToggleDoor();

    UFUNCTION()
        void SetState();
#pragma endregion

private: 
    TArray<UMeshComponent*> Meshes;
};
