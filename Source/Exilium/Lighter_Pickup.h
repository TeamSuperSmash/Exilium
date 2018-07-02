// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/MeshComponent.h"
#include "Interact_Interface.h"
#include "Lighter_Pickup.generated.h"

UCLASS()
class EXILIUM_API ALighter_Pickup : public AActor, public IInteract_Interface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALighter_Pickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
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

#pragma region LocalObjectVariables
    UPROPERTY(EditAnywhere)
        FString Name;
#pragma endregion

private:
    TArray<UMeshComponent*> Meshes;
};
