// Fill out your copyright notice in the Description page of Project Settings.

#include "RoomFogCube.h"

/*ARoomFogCube::ARoomFogCube()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARoomFogCube::BeginPlay()
{
	Super::BeginPlay();
}

void ARoomFogCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}*/

void ARoomFogCube::UpdateFogState()
{
	if (curState == ERoomFogStateEnum::NONE)
	{
		couplingRate = 0.0f;
	}
	else if (curState == ERoomFogStateEnum::STAGE_1)
	{
		couplingRate = 0.2f;
	}
	else if (curState == ERoomFogStateEnum::STAGE_2)
	{
		couplingRate = 0.5f;
	}
	else if (curState == ERoomFogStateEnum::STAGE_3)
	{
		couplingRate = 0.8f;
	}
}