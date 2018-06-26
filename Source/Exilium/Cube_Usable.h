
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/MeshComponent.h"
#include "Interact_Interface.h"
#include "Cube_Usable.generated.h"

UCLASS()
class EXILIUM_API ACube_Usable : public AActor, public IInteract_Interface
{
	GENERATED_BODY()
	
public:	
	ACube_Usable();

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

private:
    TArray<UMeshComponent*> Meshes;
	
};
