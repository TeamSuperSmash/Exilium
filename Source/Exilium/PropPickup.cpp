
#include "PropPickup.h"

APropPickup::APropPickup()
{
	PropMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	PropMesh->SetupAttachment(RootComponent);

	ItemID = FName("Undefined");
}

void APropPickup::BeginPlay()
{
	PropMesh->SetSimulatePhysics(bSimulatePhysics);
	PropMesh->SetEnableGravity(bEnableGravity);
	PropMesh->SetLinearDamping(linearDamping);
	PropMesh->SetAngularDamping(angularDamping);
}

bool APropPickup::Interact_Implementation()
{
	OnInteract();
	return true;
}

FString APropPickup::GetUseText() const
{
	//FString Name = "Item";
	//FString Action = "Pick up";

	return FString::Printf(TEXT("%s : Press E To %s"), *Name, *Action);
}
