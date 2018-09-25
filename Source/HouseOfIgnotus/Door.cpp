// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"

ADoor::ADoor()
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

void ADoor::BeginPlay()
{
	Super::BeginPlay();

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

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	doorTimeline.TickTimeline(DeltaTime);
}

void ADoor::OpenDoorCheck()
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

void ADoor::ControlDoor()
{
	timeLineValue = doorTimeline.GetPlaybackPosition();
	curveFloatValue = rotateValue * DoorCurve->GetFloatValue(timeLineValue);

	FQuat newRotation = FQuat(FRotator(0.0f, curveFloatValue, 0.0f));
	Door->SetRelativeRotation(newRotation);
}

void ADoor::ToggleDoor()
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

void ADoor::SetState()
{
	bActivated = false;
}

bool ADoor::Interact_Implementation()
{
	OnInteract();
	return true;
}