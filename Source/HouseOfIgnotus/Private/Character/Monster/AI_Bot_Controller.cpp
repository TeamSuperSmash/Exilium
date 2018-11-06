// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_Bot_Controller.h"
#include "AI_Bot_Character.h"
#include "Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Waypoint.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "PlayerCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/PawnSensingComponent.h"
#include "AI/Navigation/NavigationSystem.h"
#include "AI/Navigation/NavigationPath.h"

AAI_Bot_Controller::AAI_Bot_Controller()
{
	PrimaryActorTick.bCanEverTick = true;

	//Will soon be obsolete for this project
	//Initialize AIPerception component for AI pawn detection
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AAI_Bot_Controller::OnPawnDetected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);

	//Initialize PawnSensing component for AI pawn detection
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing Component"));

	PawnSensingComponent->OnHearNoise.AddDynamic(this, &AAI_Bot_Controller::OnNoiseHeard);

}

void AAI_Bot_Controller::BeginPlay()
{
	Super::BeginPlay();

	//Assign variables to store components
	MyCharacter = Cast<AAI_Bot_Character>(GetCharacter());
	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	AICanMove = true;
	QTEStarted = false;
	bIsPlayerDetected = false;
	heartCountDown = false;
	roomCountDown = false;
	closeChase = 0.0f;
	ChaseDuration = 5.0f;

	//Set monster state to roam
	MonsterState = EMonsterState::MS_ROAM;

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Monster State Roam"));

	CurrDetectionRadius = RoamDetectionRadius;

	PawnSensingComponent->HearingThreshold = CurrDetectionRadius;

	if(MyCharacter->NextWaypoint != nullptr)
		NavTarget = MyCharacter->NextWaypoint->GetActorLocation();

	if (GetPerceptionComponent() != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("All System Set"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Some Problem Occured"));
	}
}

void AAI_Bot_Controller::Possess(APawn *Pawn)
{
	Super::Possess(Pawn);
}

void AAI_Bot_Controller::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
	if (!AICanMove)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AI Cannot Move"));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AI Cannot Move"));
	}
	/*
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Can Move"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AI Can Move"));
	}
	*/

	if (DebugMode)
		FindPrey();
	else
		return;

	
}

FRotator AAI_Bot_Controller::GetControlRotation() const
{
	if (GetPawn() == nullptr)
	{
		return FRotator(0.0f, 0.0f, 0.0f);
	}

	return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void AAI_Bot_Controller::FindPrey()
{

	if (QTEStarted != true && bIsPlayerDetected != true)
	{

		if (FVector::Dist(MyCharacter->GetActorLocation(), Player->GetActorLocation()) <= HeartbeatDetectionRadius)
		{
			heartCountDown = true;
		}
		else
		{
			heartCountDown = false;

			//if (SeenDuration >= 0.0f)
			//	SeenDuration -= GetWorld()->DeltaTimeSeconds;
		}

		if (heartCountDown || roomCountDown)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "CountDownstart");

			SeenDuration += GetWorld()->DeltaTimeSeconds;

			if (SeenDuration >= 3.0f && MonsterState != EMonsterState::MS_CHASE)
			{
				MyCharacter->QTEStart(0);

				return;
			}
		}
		else
		{
			SeenDuration = 0.0f;
		}

	}
	/*
	else if (QTEStarted != true && bIsPlayerDetected == true)
	{
		if (FVector::Dist(MyCharacter->GetActorLocation(), Player->GetActorLocation()) <= HeartbeatDetectionRadius)
		{
			MyCharacter->QTEStart(0);

			return;
		}
	}
	*/

	FindPath();
}

void AAI_Bot_Controller::FindPath()
{
	//FVector for AI movement destination
	FVector Dest;

	//Move To Waypoint & Set Movement Speed
	if (MonsterState == EMonsterState::MS_ROAM)
	{
		if (MyCharacter->NextWaypoint != nullptr)
		{

			Dest = MyCharacter->NextWaypoint->GetActorLocation();
		}

		if (MyCharacter->MovementComponent->MaxWalkSpeed != RoamSpeed)
		{
			MyCharacter->MovementComponent->MaxWalkSpeed = RoamSpeed;
		}
	}
	else if (MonsterState == EMonsterState::MS_ALERT)
	{
		Dest = NavTarget;

		if (ChaseDuration <= 0.0f)
		{
			MonsterState = EMonsterState::MS_ROAM;

			if(MyCharacter->NextWaypoint != nullptr)
				NavTarget = MyCharacter->NextWaypoint->GetActorLocation();

			return;
		}

		if (MyCharacter->MovementComponent->MaxWalkSpeed != AlertSpeed)
		{
			MyCharacter->MovementComponent->MaxWalkSpeed = AlertSpeed;
		}
	}
	else if (MonsterState == EMonsterState::MS_CHASE)
	{
		Dest = NavTarget;

		if (ChaseDuration <= 0.0f)
		{
			MonsterState = EMonsterState::MS_ALERT;
			bIsPlayerDetected = false;

			Player->IsPlayerDangerChaseBGM = false;

			ChaseDuration = 15.0f;

			return;
		}

		if (MyCharacter->MovementComponent->MaxWalkSpeed != ChaseSpeed)
		{
			MyCharacter->MovementComponent->MaxWalkSpeed = ChaseSpeed;
		}

		if (bIsPlayerDetected == true)
		{
			NavTarget = Player->GetActorLocation();
			Dest = NavTarget;
		}
	}


	if (AICanMove)
	{
		if (MyCharacter->GetVelocity().X <= 0.1f && MyCharacter->GetVelocity().Y <= 0.1f && MyCharacter->GetVelocity().Z <= 0.1f)
		{
			ImmobilityCount -= GetWorld()->DeltaTimeSeconds;

			if (ImmobilityCount <= 0.0f)
			{
				MyCharacter->SetActorLocation(MyCharacter->NextWaypoint->GetActorLocation(), false);
				MyCharacter->NextWaypoint = MyCharacter->NextWaypoint->NextWaypoint;
				ImmobilityCount = 10.0f;
			}
		}
		else
		{
			ImmobilityCount = 10.0f;
		}

		MoveToLocation(Dest, 0.0f);


		if (MonsterState != EMonsterState::MS_ROAM && FVector::Dist(MyCharacter->GetActorLocation(), Dest) <= 100.0f)
		{
			AICanMove = false;

			return;
		}
		if (MonsterState == EMonsterState::MS_CHASE)
		{
			if (FVector::Dist(MyCharacter->GetActorLocation(), Dest) <= 150.0f)
			{
				heartCountDown = true;


				/*
				closeChase += GetWorld()->GetDeltaSeconds();

				if (closeChase >= 3.0f)
				{
					closeChase = 0.0f;

					AICanMove = false;

					return;
				}
				*/
			}
			else
			{
				heartCountDown = false;


				//closeChase = 0.0f;
			}
		}

		if (ChaseDuration >= 0.0f && MonsterState != EMonsterState::MS_ROAM)
		{
			ChaseDuration -= GetWorld()->GetDeltaSeconds();
		}

	}
	else
	{
		if (QTEStarted)
			return;
		else
		{
			if (MyCharacter->GetVelocity().X <= 0.1f && MyCharacter->GetVelocity().Y <= 0.1f && MyCharacter->GetVelocity().Z <= 0.1f)
			{
				ImmobilityCount -= GetWorld()->DeltaTimeSeconds;

				if (ImmobilityCount <= 0.0f)
				{
					if (MyCharacter->NextWaypoint != nullptr)
					{
						MonsterState = EMonsterState::MS_ROAM;
						AICanMove = true;
						MyCharacter->SetActorLocation(MyCharacter->NextWaypoint->GetActorLocation(), false);

						MyCharacter->NextWaypoint = MyCharacter->NextWaypoint->NextWaypoint;
						ImmobilityCount = 10.0f;
					}

				}
			}
			else
			{
				ImmobilityCount = 10.0f;
			}


			AIMovePause -= GetWorld()->DeltaTimeSeconds;

			if (AIMovePause <= 0.0f)
			{
				AIMovePause = 1.0f;
				AICanMove = true;

				if (MonsterState != EMonsterState::MS_ROAM)
				{

					NavTarget = UNavigationSystem::GetCurrent(GetWorld())->GetRandomReachablePointInRadius(this, MyCharacter->GetActorLocation(), RandMovementRadius);
					NavTarget.Z = MyCharacter->GetActorLocation().Z;
					AIMovePause = 0.25f;

					if (ChaseDuration <= 0.0f && bIsPlayerDetected != true)
					{
						ChaseDuration = 5.0f;

						PawnSensingComponent->HearingThreshold = AlertDetectionRadius;
						CurrDetectionRadius = AlertDetectionRadius;

						MonsterState = EMonsterState::MS_ROAM;
					}
					else if(ChaseDuration > 0.0f && bIsPlayerDetected == true)
					{
						NavTarget = UNavigationSystem::GetCurrent(GetWorld())->GetRandomReachablePointInRadius(this, Player->GetActorLocation(), RandMovementRadius);
					}
					else
					{
						PawnSensingComponent->HearingThreshold = AlertDetectionRadius;
						CurrDetectionRadius = AlertDetectionRadius;
					}
				}
				else
				{
					PawnSensingComponent->HearingThreshold = RoamDetectionRadius;
					CurrDetectionRadius = RoamDetectionRadius;
				}

			}
		}
		
	}
}


void AAI_Bot_Controller::OnPawnDetected(const TArray<AActor*> &DetectedPawns)
{
	if (MonsterState == EMonsterState::MS_ROAM)
	{
		for (size_t i = 0; i < DetectedPawns.Num(); i++)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, DetectedPawns[i]->GetName());

			CheckOpenDoors(DetectedPawns[i]);
		}
	}
}


void AAI_Bot_Controller::OnNoiseHeard(APawn* DetectedPawn, const FVector& Location, float Volume)
{
	if (DebugMode && !QTEStarted)
	{
		float distance = PawnSensingComponent->HearingThreshold;
		FHitResult hit;
		FVector startVector = MyCharacter->GetActorLocation();
		FVector endVector = Location;
		FCollisionQueryParams CollisionParams;

		CollisionParams.AddIgnoredActor(MyCharacter);


		GetWorld()->LineTraceSingleByChannel(hit, startVector, endVector, ECC_WorldStatic, CollisionParams);

		if (hit.bBlockingHit)
		{
			FVector hitDist = endVector - hit.Location;
			hitDist = hitDist.GetAbs();

			if ((hitDist.Size() / PawnSensingComponent->HearingThreshold) > 0.25f)
			{
				return;
			}
		}


		if (MonsterState == EMonsterState::MS_ROAM)
		{
			MonsterState = EMonsterState::MS_ALERT;
			ChaseDuration = 15.0f;

			PawnSensingComponent->HearingThreshold = RoamDetectionRadius;
			CurrDetectionRadius = RoamDetectionRadius;

			PlayMonsterDetectSFX();
		}

		if (FVector::Dist(MyCharacter->GetActorLocation(), Location) <= 120.0f)
		{

			if (Player != nullptr && Player->GetActorLocation() == Location)
			{
				bIsPlayerDetected = true;
				MonsterState = EMonsterState::MS_CHASE;

				ChaseDuration = 8.0f;
			}
			
		}


		NavTarget = Location;



		RandMovementRadius = 250.0f;

	}
	
}

FVector AAI_Bot_Controller::GetNextPathPoint(FVector DestPos)
{

	UNavigationPath* NavPath = UNavigationSystem::FindPathToLocationSynchronously(this, MyCharacter->GetActorLocation(), DestPos);


	if (NavPath->PathPoints.Num() > 0)
	{

		//return next path
		return NavPath->PathPoints[0];
	}

	//Return naxt waypoint as destination
	AICanMove = false;

	return NavTarget;
}




