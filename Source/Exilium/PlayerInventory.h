
#pragma once

#include "CoreMinimal.h"

class EXILIUM_API PlayerInventory
{
public:
	PlayerInventory();
	~PlayerInventory();

    TArray<FString> Items;

    void PickUpItem(FString _Item);
};
