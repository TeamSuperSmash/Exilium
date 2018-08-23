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
	player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//initialize sanity properties
	currentState = EPlayerState::NONE;
	previousState = EPlayerState::NONE;
	stayDuration = 60.0f;
	lookDuration = 5.0f;

	//initialize post processing Dynamic Material Instance
	TArray<UPostProcessComponent*> pcomps;
	player->GetComponents<UPostProcessComponent>(pcomps);
	postComp = pcomps[0];
	sanityDMI = UMaterialInstanceDynamic::Create(sanityMat, this);
	sanityDMI->SetScalarParameterValue("Strength", currentSanity / 10.0f);
	FPostProcessVolumeProperties prop = postComp->GetProperties();

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
		float strength = FMath::Lerp(0.0f, 0.09f, currentSanity / 90.0f);
		sanityDMI->SetScalarParameterValue("Strength", strength); //invlove post processing
		float curThreshold = (static_cast<int>(player->SanityState) * sanityThresholdGap) + sanityThresholdGap;
		float insanityIncrement = sanityThresholdGap / stayDuration;

		if (fogTimer >= 1.0f)
		{
			fogTimer = 0;
			fogCounter++;

			if (currentSanity + insanityIncrement < curThreshold)
			{
				currentSanity += insanityIncrement;
			}
		}

		if (fogCounter >= stayDuration)
		{
			fogCounter = 0;
			fogTimer = 0;
			previousState = EPlayerState::INFOG;
			currentState = EPlayerState::BREATHINGMINI;
		}
	}
}

void USanityComponent::ChangePlayerState(EPlayerState state)
{
	previousState = currentState;
	currentState = state;
}

void USanityComponent::UpdateSanity()
{
	for (int i = 0; i < int(ESanityState::SANITY_LEVEL_3); i++)
	{
		if (currentSanity >= i * sanityThresholdGap && currentSanity < (i + 1)* sanityThresholdGap)
		{
			player->SanityState = ESanityState(i);
			break;
		}
	}
}

//void 
//! legacy for UpdatePlayerState
	/*else if (currentState == EPlayerState::LOOKATMONSTER)
	{
		// check rendered function(do in blue print)
		/*lookTimer += deltaTime;
		if (lookTimer >= lookDuration)
		{
			lookTimer = 0;
			previousState = EPlayerState::LOOKATMONSTER;
			currentState = EPlayerState::BREATHINGMINI;
			//trigger breating mini game
		}
	}*/
	/*else if (currentState == EPlayerState::BREATHINGMINI)
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
	}*/


