// Fill out your copyright notice in the Description page of Project Settings.

#include "FogCube_Manager.h"


// Sets default values
AFogCube_Manager::AFogCube_Manager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFogCube_Manager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFogCube_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFogCube_Manager::checkCurrent(AFogCube* cube)
{
	if (cube != current)
	{
		current->Reduce(cube);
		cube->Spread();
		current = cube;
	}
}

