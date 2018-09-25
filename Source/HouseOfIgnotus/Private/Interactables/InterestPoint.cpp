// Fill out your copyright notice in the Description page of Project Settings.

#include "InterestPoint.h"


// Sets default values
AInterestPoint::AInterestPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInterestPoint::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInterestPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AInterestPoint::CheckMatch()
{
	return isSettled;
}

/*void AInterestPoint::UpdateState()
{
	if (slot == item)
	{
		isSettled = true;
	}
	else
	{
		isSettled = false;
	}
}

void AInterestPoint::SetItem(EPuzzlePropsTypeEnum var)
{
	item = var;
	UpdateState();
}*/



