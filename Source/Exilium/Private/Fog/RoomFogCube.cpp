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


/*void ARoomFogCube::CheckPuzzleProgress()
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
		isNormalized = true;
	}
	else
	{
		isNormalized = false;
		curState = static_cast<ERoomFogStateEnum>(count);
		debugCount = count;
	}
}*/

void ARoomFogCube::UpdateFogState()
{
	if (curState == ERoomFogStateEnum::NONE)
	{
		couplingRate = 0.0f;
		//SetCouplingRate(1.0f, 0.0f, couplingRate, deltaTime);
	}
	else if (curState == ERoomFogStateEnum::DENSE)
	{
		couplingRate = 0.7f;
		//SetCouplingRate(1.0f, 0.7f,couplingRate, deltaTime);
	}
	else if (curState == ERoomFogStateEnum::MEDIUM)
	{
		couplingRate = 0.4f;
		//SetCouplingRate(1.0f, 0.4f, couplingRate, deltaTime);
	}
	else if (curState == ERoomFogStateEnum::LESS)
	{
		couplingRate = 0.2f;
		//SetCouplingRate(1.0f, 0.2f, couplingRate, deltaTime);
	}
}

void ARoomFogCube::SetCouplingRate(float duration,float targetRate,float currentRate,float deltaTime)
{
	if (currentRate > targetRate)
	{
		timer += deltaTime;
		if(timer >= duration)
		{
			timer = 0;
			currentRate -= 0.1f;
			couplingRate -= 0.1f;
		}
	}
	else if(currentRate < targetRate)
	{
		timer += deltaTime;
		if (timer >= duration)
		{
			timer = 0;
			currentRate += 0.1f;
		}
	}
}