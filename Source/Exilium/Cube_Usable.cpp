
#include "Cube_Usable.h"

ACube_Usable::ACube_Usable()
{
	PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;

}

void ACube_Usable::BeginPlay()
{
	Super::BeginPlay();
    
    for (UActorComponent* Comp : GetComponentsByClass(UMeshComponent::StaticClass()))
    {
        UMeshComponent* Mesh = Cast<UMeshComponent>(Comp);
        Meshes.Push(Mesh);
    }
}

void ACube_Usable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACube_Usable::OnInteract_Implementation(AActor * Caller)
{
    Destroy();

    //Add a widget reference with text saying the player has picked up item.
    
    UE_LOG(LogTemp, Warning, TEXT("Interact Item"));
}

void ACube_Usable::StartFocus_Implementation()
{
    for (UMeshComponent* Mesh : Meshes)
    {
        Mesh->SetRenderCustomDepth(true);
        UE_LOG(LogTemp, Warning, TEXT("Cube ON"));
    }
}

void ACube_Usable::EndFocus_Implementation()
{
    for (UMeshComponent* Mesh : Meshes)
    {
        Mesh->SetRenderCustomDepth(false);
        UE_LOG(LogTemp, Warning, TEXT("Cube OFF"));
    }
}

