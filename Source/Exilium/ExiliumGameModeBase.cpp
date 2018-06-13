// Fill out your copyright notice in the Description page of Project Settings.

#include "ExiliumGameModeBase.h"
#include "Exilium.h"

void AExiliumGameModeBase::StartPlay()
{
    Super::StartPlay();

    if (GEngine)
    {
        // Display the debug message log for five seconds.
        // The -1 key value (first argument) indicates that we will never need
        // to update or refresh this message.

        //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World!"));
    }
}



