// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Exilium.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
    if (GEngine)
    {
        //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Using PlayerCharacter!"));
    }

    UE_LOG(LogTemp, Warning, TEXT("Starting PlayerCharacter"));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Set up "move" bindings.
    PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

    // Set up "look" bindings.
    PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);

    // Set up "action" bindings.
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJump);
}

void APlayerCharacter::MoveForward(float _value)
{
    FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
    AddMovementInput(Direction, _value);
}

void APlayerCharacter::MoveRight(float _value)
{
    FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
    AddMovementInput(Direction, _value);
}

void APlayerCharacter::StartJump()
{
    //bPressedJump = true;

    FVector jumpVelocity = GetVelocity();

    jumpVelocity += FVector(0.0f, 0.0f, 100.0f);

}

void APlayerCharacter::StopJump()
{
    //bPressedJump = false;
}

