// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"

APickup::APickup()
{
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	PickupMesh->SetupAttachment(RootComponent);

	ItemID = FName("Undefined");
}

void APickup::BeginPlay()
{
	PickupMesh->SetSimulatePhysics(bSimulatePhysics);
	PickupMesh->SetEnableGravity(bEnableGravity);
	PickupMesh->SetLinearDamping(linearDamping);
	PickupMesh->SetAngularDamping(angularDamping);
}

bool APickup::Interact_Implementation()
{
	OnInteract();
	return true;
}

FString APickup::GetUseText() const
{
	//FString Name = "Item";
	//FString Action = "Pick up";

	return FString::Printf(TEXT("%s : Press E To %s"), *Name, *Action);
}
