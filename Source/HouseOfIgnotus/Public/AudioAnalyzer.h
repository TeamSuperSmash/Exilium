// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FMODBlueprintStatics.h"
#include "AudioAnalyzer.generated.h"
/**
 * 
 */
UCLASS()
class HOUSEOFIGNOTUS_API UAudioAnalyzer : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Catergory = Init)
		int32 InitializeAudioAnalyzer();
	UFUNCTION(BlueprintCallable, Category = Init)
		int32 InitSpectrum_Linear(const int32 numBars);
	UFUNCTION(BlueprintCallable, Category = Actions)
		void Update();
	UFUNCTION(BlueprintCallable, Category = Access)
		void GetSpectrum_Linear(TArray<float>& frequencyValues, TArray<float>& frequencyAverageValues, const int32 effectiveBars);
	UFUNCTION(BlueprintCallable, Category = Actions)
		FFMODEventInstance PlayEventAtLocation(UObject* WorldContextObject, UFMODEvent* Event, const FTransform& Location, bool bAutoPlay);

	UAudioAnalyzer();
	~UAudioAnalyzer();

};
