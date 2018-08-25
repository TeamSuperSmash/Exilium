// Fill out your copyright notice in the Description page of Project Settings.

#include "WeirdDoor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "EngineGlobals.h"
#include "Engine/Engine.h"

// Sets default values
AWeirdDoor::AWeirdDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isOpened = false;
	isReady = true;
}

// Called before BeginPlay()
void AWeirdDoor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Awake();
}

// Called when the game starts or when spawned
void AWeirdDoor::BeginPlay()
{
	Super::BeginPlay();

	EnableInput(UGameplayStatics::GetPlayerController(this, 0));

	rotateDirection = 1.0f;

	if (animationCurve)
	{
		FOnTimelineFloat timelineCallback;
		FOnTimelineEventStatic timelineFinishedCallback;

		timelineCallback.BindUFunction(this, FName("ControlDoor"));
		timelineFinishedCallback.BindUFunction(this, FName("SetState"));

		doorTimeline.AddInterpFloat(animationCurve, timelineCallback);
		doorTimeline.SetTimelineFinishedFunc(timelineFinishedCallback);
	}
}

// Called every frame
void AWeirdDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	doorTimeline.TickTimeline(DeltaTime);
}

void AWeirdDoor::InitializeComponents(USceneComponent* rotator, USceneComponent* rotator_bottom, USceneComponent* rotator_center)
{
	m_rotator = rotator;
	m_rotator_bottom = rotator_bottom;
	m_rotator_center = rotator_center;
}

USceneComponent* AWeirdDoor::GetRotator()
{
	return m_rotator;
}

USceneComponent* AWeirdDoor::GetRotatorBottom()
{
	return m_rotator_bottom;
}

USceneComponent* AWeirdDoor::GetRotatorCenter()
{
	return m_rotator_center;
}

void AWeirdDoor::ControlDoor()
{
	float TimelineValue = doorTimeline.GetPlaybackPosition();

	if (handlePosition == EHandlePosition::HP_Center)
	{
		float CurveFloatValue = rotateDirection * animationCurve->GetFloatValue(TimelineValue);
		GetRotator()->SetRelativeRotation(FRotator(0.0f, CurveFloatValue, 0.0f));
		GetRotatorBottom()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		GetRotatorCenter()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (handlePosition == EHandlePosition::HP_Top)
	{
		float CurveFloatValue = rotateDirection * animationCurve->GetFloatValue(TimelineValue);
		GetRotator()->SetRelativeRotation(FRotator(CurveFloatValue, 0.0f, 0.0f));
		GetRotatorBottom()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		GetRotatorCenter()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (handlePosition == EHandlePosition::HP_Bottom)
	{
		float CurveFloatValue = rotateDirection * animationCurve->GetFloatValue(TimelineValue);
		GetRotator()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		GetRotatorBottom()->SetRelativeRotation(FRotator(0.0f, CurveFloatValue, 0.0f));
		GetRotatorCenter()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
	else if (handlePosition == EHandlePosition::HP_RotatedVertically)
	{
		float CurveFloatValue = rotateDirection * animationCurve->GetFloatValue(TimelineValue);
		GetRotator()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		GetRotatorBottom()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		GetRotatorCenter()->SetRelativeRotation(FRotator(0.0f, -CurveFloatValue, 0.0f));
	}
	else if (handlePosition == EHandlePosition::HP_RotatedSideways)
	{
		float CurveFloatValue = animationCurve->GetFloatValue(TimelineValue);
		GetRotator()->SetRelativeRotation(FRotator(0.0f, 0.0f, CurveFloatValue));
		GetRotatorBottom()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		GetRotatorCenter()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
}

void AWeirdDoor::SetState()
{
	isReady = true;
}

bool AWeirdDoor::Interact_Implementation()
{
	//if (isReady)
	//{
	//	isOpened = !isOpened;
	//
	//	APawn* Player = UGameplayStatics::GetPlayerPawn(this, 0);
	//	FVector Direction = GetActorLocation() - Player->GetActorLocation();
	//	Direction = UKismetMathLibrary::LessLess_VectorRotator(Direction, GetActorRotation());
	//
	//	if (isOpened)
	//	{
	//		if (Direction.X >= 0.0f)
	//		{
	//			rotateDirection = 1.0f;
	//		}
	//		else
	//		{
	//			rotateDirection = -1.0f;
	//		}
	//
	//		isReady = false;
	//		doorTimeline.PlayFromStart();
	//	}
	//	else
	//	{
	//		isReady = false;
	//		doorTimeline.Reverse();
	//	}
	//
	//	this->OnInteract();
	//	return true;
	//}
	//return false;

	this->OnInteract();
	return true;
}

void AWeirdDoor::Debug_ChangeDoorHandlePosition()
{
	handlePosition = static_cast<EHandlePosition>((static_cast<int>(handlePosition) + 1) % static_cast<int>(EHandlePosition::HP_Total));
}
