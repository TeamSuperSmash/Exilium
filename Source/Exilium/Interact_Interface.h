
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerCharacter.h"
#include "Interact_Interface.generated.h"

UINTERFACE(MinimalAPI)
class UInteract_Interface : public UInterface
{
	GENERATED_BODY()
};

class EXILIUM_API IInteract_Interface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
        void OnInteract(AActor* Caller);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
        void StartFocus();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
        void EndFocus();

};
