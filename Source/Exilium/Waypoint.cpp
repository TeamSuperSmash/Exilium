// Fill out your copyright notice in the Description page of Project Settings.

#include "Waypoint.h"
#include "AI_Bot_Character.h"
#include "AI_Bot_Controller.h"
#include "Perception/PawnSensingComponent.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "PlayerCharacter.h"


// Sets default values
AWaypoint::AWaypoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	SetRootComponent(Root);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	BoxComponent->SetupAttachment(GetRootComponent());
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AWaypoint::OnPlayerEnter);
}

// Called when the game starts or when spawned
void AWaypoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaypoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaypoint::OnPlayerEnter(UPrimitiveComponent* OverlapComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult &SweepResult)
{
	AAI_Bot_Character* Character = nullptr;

	if (OtherActor != nullptr)
	{
		Character = Cast<AAI_Bot_Character>(OtherActor);

		if (Character != nullptr)
		{
			if (Character->MyController->MonsterState == EMonsterState::MS_ROAM && Character->NextWaypoint == this)
			{
				Character->NextWaypoint = NextWaypoint;
				Character->MyController->NavTarget = NextWaypoint->GetActorLocation();

				Character->MyController->AICanMove = false;
				Character->MyController->PawnSensingComponent->HearingThreshold = Character->MyController->SpecialDetectionRadius;
				Character->MyController->CurrDetectionRadius = Character->MyController->SpecialDetectionRadius;

				//Character->MyController->Player->GetPawnNoiseEmitterComponent()->MakeNoise(Character->MyController->Player, 1.0f,
				//											Character->MyController->Player->GetActorLocation());
			}
		}
	}
}
