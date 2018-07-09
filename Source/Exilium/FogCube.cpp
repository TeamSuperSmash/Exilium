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
	//isActive = true;
}

// Called every frame
void AFogCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!isActive)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I am false"));
		SetActorEnableCollision(false);
		SetActorHiddenInGame(true);
	}
}

void AFogCube::RegisterDelegate()
{

}

