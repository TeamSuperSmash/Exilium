// Fill out your copyright notice in the Description page of Project Settings.

#include "ScareManager.h"


// Sets default values
AScareManager::AScareManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AScareManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AScareManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AScareManager::GetRandomScare(TScriptInterface<IMutatable> &Interface, bool &isSucceed)
{
	int min = 0;
	int max = scareObjects.Num() - 1;
	int randNum = FMath::RandRange(min, max);

	AActor* randActor = scareObjects[randNum];

	if (randActor->GetClass()->ImplementsInterface(UMutatable::StaticClass()))
	{
		Interface.SetInterface(Cast<IMutatable>(randActor));
		Interface.SetObject(randActor);

		isSucceed = true;
		return;
	}

	isSucceed = false;
}
