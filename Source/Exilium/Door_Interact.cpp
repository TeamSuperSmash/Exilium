// Fill out your copyright notice in the Description page of Project Settings.

#include "Door_Interact.h"

ADoor_Interact::ADoor_Interact()
{
	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>("DoorFrame");
	Door = CreateDefaultSubobject<UStaticMeshComponent>("Door");

	Door->SetupAttachment(DoorFrame);
}


