
#include "Door_Usable.h"

ADoor_Usable::ADoor_Usable()
{
 	PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
    bActivated = false;
    bOpened = false;

	rotateValue = 1.0f;

    DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
    Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
    Door->SetupAttachment(DoorFrame);
}

void ADoor_Usable::BeginPlay()
{
	Super::BeginPlay();

	for (UActorComponent* Comp : GetComponentsByClass(UMeshComponent::StaticClass()))
	{
		UMeshComponent* Mesh = Cast<UMeshComponent>(Comp);
		Meshes.Push(Mesh);
	}

    if (DoorCurve)
    {
        FOnTimelineFloat TimelineCallback;
        FOnTimelineEventStatic TimelineFinishedCallback;

        TimelineCallback.BindUFunction(this, FName("ControlDoor"));
        TimelineFinishedCallback.BindUFunction(this, FName("SetState"));

        doorTimeline.AddInterpFloat(DoorCurve, TimelineCallback);
        doorTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
    }
}

void ADoor_Usable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    doorTimeline.TickTimeline(DeltaTime);
}

void ADoor_Usable::OnInteract_Implementation(AActor* Caller)
{
    ToggleDoor();
    UE_LOG(LogTemp, Warning, TEXT("Interact Item"));
}

void ADoor_Usable::StartFocus_Implementation()
{
	for (UMeshComponent* Mesh : Meshes)
	{
		Mesh->SetRenderCustomDepth(true);
		UE_LOG(LogTemp, Warning, TEXT("Door ON"));
	}
}

void ADoor_Usable::EndFocus_Implementation()
{
	for (UMeshComponent* Mesh : Meshes)
	{
        Mesh->SetRenderCustomDepth(false);
		UE_LOG(LogTemp, Warning, TEXT("Door OFF"));
	}
}

void ADoor_Usable::OpenDoorCheck()
{
    if (!bOpened)
    {
        FVector CurrentLoc = GetActorLocation();
        FVector TargetLoc = FVector(CurrentLoc.X, CurrentLoc.Y, CurrentLoc.Z + 10.0f);
        FVector NewLoc = FMath::Lerp(CurrentLoc, TargetLoc, 10.0f);

        SetActorLocation(NewLoc);

        bOpened = true;
    }
    else
    {
        FVector CurrentLoc = GetActorLocation();
        FVector TargetLoc = FVector(CurrentLoc.X, CurrentLoc.Y, CurrentLoc.Z - 10.0f);
        FVector NewLoc = FMath::Lerp(CurrentLoc, TargetLoc, 10.0f);

        SetActorLocation(NewLoc);

        bOpened = false;
    }
}

void ADoor_Usable::ControlDoor()
{
    timeLineValue = doorTimeline.GetPlaybackPosition();
    curveFloatValue = rotateValue * DoorCurve->GetFloatValue(timeLineValue);

    FQuat newRotation = FQuat(FRotator(0.0f, curveFloatValue, 0.0f));
    Door->SetRelativeRotation(newRotation);
}

void ADoor_Usable::ToggleDoor()
{
    if (!bActivated)
    {
        bOpened = !bOpened;

        APawn* playerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
        FVector pawnLocation = playerPawn->GetActorLocation();
        FVector direction = GetActorLocation() - pawnLocation;
        direction = UKismetMathLibrary::LessLess_VectorRotator(direction, GetActorRotation());

        doorRotation = Door->RelativeRotation;

        if (bOpened)
        {
            if (direction.X > 0.0f)
            {
                rotateValue = 1.0f;
            }
            else
            {
                rotateValue = -1.0f;
            }

            bActivated = true;
            doorTimeline.PlayFromStart();
        }
        else
        {
            bActivated = true;
            doorTimeline.Reverse();
        }
    }
}

void ADoor_Usable::SetState()
{
    bActivated = false;
}

