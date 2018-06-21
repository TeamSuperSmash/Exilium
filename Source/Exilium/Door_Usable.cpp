
#include "Door_Usable.h"

ADoor_Usable::ADoor_Usable()
{
 	PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
}

void ADoor_Usable::BeginPlay()
{
	Super::BeginPlay();
	
    for (UActorComponent* Comp : GetComponentsByClass(UMeshComponent::StaticClass()))
    {
        UMeshComponent* Mesh = Cast<UMeshComponent>(Comp);
        Meshes.Push(Mesh);
    }
}

void ADoor_Usable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor_Usable::OnInteract_Implementation(AActor* Caller)
{
    //Destroy();
    FVector CurrentLoc = GetActorLocation();
    FVector TargetLoc = FVector(CurrentLoc.X, CurrentLoc.Y, CurrentLoc.Z + 10.0f);
    FVector NewLoc = FMath::Lerp(CurrentLoc, TargetLoc, 10.0f);
    
    SetActorLocation(NewLoc);

    UE_LOG(LogTemp, Warning, TEXT("Interact Item"));
}

void ADoor_Usable::StartFocus_Implementation()
{
    for (UMeshComponent* Mesh : Meshes)
    {
        Mesh->SetRenderCustomDepth(true);
        GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, FString::Printf(TEXT("Focus ON")));
        UE_LOG(LogTemp, Warning, TEXT("Focus ON"));
    }
}

void ADoor_Usable::EndFocus_Implementation()
{
    for (UMeshComponent* Mesh : Meshes)
    {
        Mesh->SetRenderCustomDepth(false);
        GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, FString::Printf(TEXT("Focus OFF")));
        UE_LOG(LogTemp, Warning, TEXT("Focus OFF"));
    }
}

