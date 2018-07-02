// Fill out your copyright notice in the Description page of Project Settings.

#include "Lighter_Pickup.h"


// Sets default values
ALighter_Pickup::ALighter_Pickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;

    Name = "Lighter";
}

// Called when the game starts or when spawned
void ALighter_Pickup::BeginPlay()
{
	Super::BeginPlay();

    for (UActorComponent* Comp : GetComponentsByClass(UMeshComponent::StaticClass()))
    {
        UMeshComponent* Mesh = Cast<UMeshComponent>(Comp);
        Meshes.Push(Mesh);
    }
}

// Called every frame
void ALighter_Pickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALighter_Pickup::OnInteract_Implementation(AActor * Caller)
{
    Destroy();

    //Add a widget reference with text saying the player has picked up item.

    UE_LOG(LogTemp, Warning, TEXT("Interact Item"));
}

void ALighter_Pickup::StartFocus_Implementation()
{
    for (UMeshComponent* Mesh : Meshes)
    {
        Mesh->SetRenderCustomDepth(true);
        UE_LOG(LogTemp, Warning, TEXT("Lighter ON"));
    }
}

void ALighter_Pickup::EndFocus_Implementation()
{
    for (UMeshComponent* Mesh : Meshes)
    {
        Mesh->SetRenderCustomDepth(false);
        UE_LOG(LogTemp, Warning, TEXT("Lighter OFF"));
    }
}