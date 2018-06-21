
#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Components/MeshComponent.h"
#include "Interact_Interface.h"
#include "GameFramework/Actor.h"
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

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void OnInteract(AActor* Caller);
    virtual void OnInteract_Implementation(AActor* Caller) override;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void StartFocus();
    virtual void StartFocus_Implementation() override;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void EndFocus();
    virtual void EndFocus_Implementation() override;
	
private: 
    TArray<UMeshComponent*> Meshes;
};
