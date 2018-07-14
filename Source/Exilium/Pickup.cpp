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
