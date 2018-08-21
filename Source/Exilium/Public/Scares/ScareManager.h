// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mutatable.h"
#include "ScareManager.generated.h"

UCLASS()
class EXILIUM_API AScareManager : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scare Manager")
	TArray<AActor*> scareObjects;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Scare Manager")
	TArray<TScriptInterface<IMutatable>> cachedObjects;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (DisplayName = "Cached Time (Native Condition)"), Category = "Scare Manager")
	TArray<float> cachedTimes;

public:	
	// Sets default values for this actor's properties
	AScareManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable, Category="Scare Manager")
	void GetRandomScare(TScriptInterface<IMutatable> &Interface, bool &isSucceed);
	
};
