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

void ARoomFogCube::CheckPuzzleProgress()
{
	int count = 1;
	for (int i = 0; i < puzzleList.Num(); i++)
	{
		if (puzzleList[i]->GetState() == true)
		{
			count+=1;
		}
	}

	if (count == static_cast<int>(ERoomFogStateEnum::_MAX))
	{
		curState = ERoomFogStateEnum::NONE;
	}
	else
	{
		curState = static_cast<ERoomFogStateEnum>(count);
		debugCount = count;
	}
}

void ARoomFogCube::UpdateFogState()
{
	if (curState == ERoomFogStateEnum::NONE)
	{
		couplingRate = 0.0f;
	}
	else if (curState == ERoomFogStateEnum::DENSE)
	{
		couplingRate = 0.7f;
	}
	else if (curState == ERoomFogStateEnum::MEDIUM)
	{
		couplingRate = 0.4f;
	}
	else if (curState == ERoomFogStateEnum::LESS)
	{
		couplingRate = 0.2f;
	}
}