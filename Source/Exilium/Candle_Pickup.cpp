// Fill out your copyright notice in the Description page of Project Settings.

#include "Candle_Pickup.h"


// Sets default values
ACandle_Pickup::ACandle_Pickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;

    Name = "Candle";
}

// Called when the game starts or when spawned
void ACandle_Pickup::BeginPlay()
{
	Super::BeginPlay();

    for (UActorComponent* Comp : GetComponentsByClass(UMeshComponent::StaticClass()))
    {
        UMeshComponent* Mesh = Cast<UMeshComponent>(Comp);
        Meshes.Push(Mesh);
    }
}

// Called every frame
void ACandle_Pickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACandle_Pickup::OnInteract_Implementation(AActor * Caller)
{
    Destroy();

    //Add a widget reference with text saying the player has picked up item.

    UE_LOG(LogTemp, Warning, TEXT("Interact Item"));
}

void ACandle_Pickup::StartFocus_Implementation()
{
    for (UMeshComponent* Mesh : Meshes)
    {
        Mesh->SetRenderCustomDepth(true);
        UE_LOG(LogTemp, Warning, TEXT("Candle ON"));
    }
}

void ACandle_Pickup::EndFocus_Implementation()
{
    for (UMeshComponent* Mesh : Meshes)
    {
        Mesh->SetRenderCustomDepth(false);
        UE_LOG(LogTemp, Warning, TEXT("Candle OFF"));
    }
}