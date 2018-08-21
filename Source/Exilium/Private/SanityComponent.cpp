// Fill out your copyright notice in the Description page of Project Settings.

#include "SanityComponent.h"


// Sets default values for this component's properties
USanityComponent::USanityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USanityComponent::BeginPlay()
{
	Super::BeginPlay();
	//initialize sanity properties
	currentState = EPlayerState::NONE;
	previousState = EPlayerState::NONE;
	stayDuration = 60.0f;
	lookDuration = 5.0f;
}


// Called every frame
void USanityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USanityComponent::CheckValidFogState()
{
	if (currentState == EPlayerState::NONE || currentState == EPlayerState::INFOG)
	{
		currentState = EPlayerState::INFOG;
	}
}

void USanityComponent::UpdatePlayerState(float deltaTime)
{
	float strength = FMath::Lerp(0.0f, 0.09f, currentSanity / 90.0f);
	//sanityDMI->SetScalarParameterValue("Strength", strength); //invlove post processing
	if (currentState == EPlayerState::NONE)
	{
		if (fogCounter > 0)
		{
			fogTimer += deltaTime;
			if (fogTimer >= 1.0f)
			{
				fogTimer = 0;
				fogCounter--;
			}
		}
		if (lookDuration > 0)
		{
			lookDuration -= deltaTime;
		}
	}
	else if (currentState == EPlayerState::INFOG)
	{
		fogTimer += deltaTime;
		//float curThreshold = (static_cast<int>(SanityState) * sanityThresholdGap) + sanityThresholdGap;
		float insanityIncrement = sanityThresholdGap / stayDuration;

		if (fogTimer >= 1.0f)
		{
			fogTimer = 0;
			fogCounter++;

			/*if (currentSanity + insanityIncrement < curThreshold)
			{
				currentSanity += insanityIncrement;
			}*/
		}

		if (fogCounter >= stayDuration)
		{
			fogCounter = 0;
			fogTimer = 0;
			previousState = EPlayerState::INFOG;
			currentState = EPlayerState::BREATHINGMINI;
		}
	}
	else if (currentState == EPlayerState::LOOKATMONSTER)
	{
		// need to integrate with Naim and Luqman's code
		lookTimer += deltaTime;
		if (lookTimer >= lookDuration)
		{
			lookTimer = 0;
			//! --monster move toward function
			previousState = EPlayerState::LOOKATMONSTER;
			currentState = EPlayerState::BREATHINGMINI;
			//trigger breating mini game
		}
	}
	else if (currentState == EPlayerState::BREATHINGMINI)
	{
		//currentSanity = (static_cast<int>(SanityState) * sanityThresholdGap) + sanityThresholdGap;
		currentState = previousState;

		//! --if success
		//! --change music
		//! --set sanity
		//! --set to previosState
		//! --else 
		//! --change music
		//currentState = EPlayerState::HEARTBEATMINI;
	}
	else if (currentState == EPlayerState::HEARTBEATMINI)
	{
		//lose
	}
}

