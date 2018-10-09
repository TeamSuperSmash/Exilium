// Fill out your copyright notice in the Description page of Project Settings.

#include "AudioAnalyzer.h"
#include "fmod_studio.hpp"
#include "FMODEvent.h"

int32 UAudioAnalyzer::InitSpectrum_Linear(const int32 numBars)
{
	return int32();
}

void UAudioAnalyzer::Update()
{

}

void UAudioAnalyzer::GetSpectrum_Linear(TArray<float>& frequencyValues, TArray<float>& frequencyAverageValues, const int32 effectiveBars)
{
}

FFMODEventInstance UAudioAnalyzer::PlayEventAtLocation(UObject * WorldContextObject, UFMODEvent * Event, const FTransform & Location, bool bAutoPlay)
{
	FFMODEventInstance Instance;
	Instance.Instance = nullptr;

	UWorld* ThisWorld = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
	if (FMODUtils::IsWorldAudible(ThisWorld, false))
	{
		FMOD::Studio::EventDescription* EventDesc = IFMODStudioModule::Get().GetEventDescription(Event);
		if (EventDesc != nullptr)
		{
			FMOD::Studio::EventInstance* EventInst = nullptr;
			EventDesc->createInstance(&EventInst);
			if (EventInst != nullptr)
			{
				FMOD_3D_ATTRIBUTES EventAttr = { { 0 } };
				FMODUtils::Assign(EventAttr, Location);
				EventInst->set3DAttributes(&EventAttr);

				if (bAutoPlay)
				{
					EventInst->start();
					EventInst->release();
				}
				Instance.Instance = EventInst;
			}
		}
	}
	return Instance;
}
