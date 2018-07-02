
#include "PlayerInventory.h"

PlayerInventory::PlayerInventory()
{
}

PlayerInventory::~PlayerInventory()
{
}

void PlayerInventory::PickUpItem(FString _Item)
{
    Items.Add(_Item);
}
