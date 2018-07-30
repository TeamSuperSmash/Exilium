// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_Bot_Character.h"
#include "AI_Bot_Controller.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter.h"


// Sets default values
AAI_Bot_Character::AAI_Bot_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 600.0f, 0.0f);

}

void AAI_Bot_Character::EventFailQTE()
{
	bIsPlayerDetected = true;

	MyController->bIsPlayerDetected = true;

	MyController->MonsterState = EMonsterState::MS_CHASE;


	MyController->ChaseDuration = 5.0f;
	MyController->AICanMove = true;

	MyController->PawnSensingComponent->HearingThreshold = MyController->AlertDetectionRadius;
	MyController->CurrDetectionRadius = MyController->AlertDetectionRadius;
}

void AAI_Bot_Character::HeartbeatSuccess()
{
	MyController->bIsPlayerDetected = false;

	MyController->NavTarget = MyController->Player->GetActorLocation();

	MyController->MonsterState = EMonsterState::MS_ALERT;
}

// Called when the game starts or when spawned
void AAI_Bot_Character::BeginPlay()
{
	Super::BeginPlay();
	
	MyController = Cast<AAI_Bot_Controller>(GetController());
	MovementComponent = Cast<UCharacterMovementComponent>(GetCharacterMovement());

}

// Called every frame
void AAI_Bot_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAI_Bot_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

