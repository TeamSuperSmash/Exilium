// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable.h"

AInteractable::AInteractable()
{
	Name = "Undefined";
	Action = "Interact";
}

void AInteractable::BeginPlay()
{
	Super::BeginPlay();	
}
