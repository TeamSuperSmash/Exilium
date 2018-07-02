// Fill out your copyright notice in the Description page of Project Settings.

#include "MusicBox_Pickup.h"


// Sets default values
AMusicBox_Pickup::AMusicBox_Pickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;

    Name = "Music Box";
}

// Called when the game starts or when spawned
void AMusicBox_Pickup::BeginPlay()
{
	Super::BeginPlay();

    for (UActorComponent* Comp : GetComponentsByClass(UMeshComponent::StaticClass()))
    {
        UMeshComponent* Mesh = Cast<UMeshComponent>(Comp);
        Meshes.Push(Mesh);
    }
}

// Called every frame
void AMusicBox_Pickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMusicBox_Pickup::OnInteract_Implementation(AActor * Caller)
{
    Destroy();

    //Add a widget reference with text saying the player has picked up item.

    UE_LOG(LogTemp, Warning, TEXT("Interact Item"));
}

void AMusicBox_Pickup::StartFocus_Implementation()
{
    for (UMeshComponent* Mesh : Meshes)
    {
        Mesh->SetRenderCustomDepth(true);
        UE_LOG(LogTemp, Warning, TEXT("Music Box ON"));
    }
}

void AMusicBox_Pickup::EndFocus_Implementation()
{
    for (UMeshComponent* Mesh : Meshes)
    {
        Mesh->SetRenderCustomDepth(false);
        UE_LOG(LogTemp, Warning, TEXT("Music Box OFF"));
    }
}