// Fill out your copyright notice in the Description page of Project Settings.

#include "FogCube.h"


// Sets default values
AFogCube::AFogCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFogCube::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFogCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFogCube::SetActive(bool value)
{
	SetActorHiddenInGame(!value);
}

void AFogCube::Spread()
{
	isActive = true;
	for (int i = 0; i < neighbour.Num(); i++)
	{
		if (neighbour[i] != nullptr)
		{
			neighbour[i]->isActive = true;
		}
	}
}


void AFogCube::Reduce(AFogCube* exclude)
{
	for (int i = 0; i < neighbour.Num(); i++)
	{
		if (neighbour[i] != exclude && neighbour[i] != nullptr)
		{
			neighbour[i]->isActive = false;
		}
	}
}


