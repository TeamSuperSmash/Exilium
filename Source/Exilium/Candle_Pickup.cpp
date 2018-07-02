// Fill out your copyright notice in the Description page of Project Settings.

#include "Candle_Pickup.h"


// Sets default values
ACandle_Pickup::ACandle_Pickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACandle_Pickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACandle_Pickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

