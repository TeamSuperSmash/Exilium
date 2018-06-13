// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Exilium.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    currentSpeed = GetCharacterMovement()->MaxWalkSpeed;

    GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
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

    if (bSprinting && bForward && !bCrouching)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player is sprinting!"));
        GetCharacterMovement()->MaxWalkSpeed = currentSpeed * sprintMultiplier;
    }
    else
    {
        GetCharacterMovement()->MaxWalkSpeed = currentSpeed;
    }
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
    PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::StartCrouch);
    PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APlayerCharacter::StopCrouch);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::StartSprint);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::StopSprint);
    PlayerInputComponent->BindAction("ForwardKey", IE_Pressed, this, &APlayerCharacter::StartForward);
    PlayerInputComponent->BindAction("ForwardKey", IE_Released, this, &APlayerCharacter::StopForward);
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
    bPressedJump = true;
}

void APlayerCharacter::StopJump()
{
    bPressedJump = false;
}

void APlayerCharacter::StartCrouch()
{
    bCrouching = true;
    Crouch();
}

void APlayerCharacter::StopCrouch()
{
    bCrouching = false;
    UnCrouch();
}

void APlayerCharacter::StartSprint()
{
    bSprinting = true;
}

void APlayerCharacter::StopSprint()
{
    bSprinting = false;
}

void APlayerCharacter::StartForward()
{
    bForward = true;
}

void APlayerCharacter::StopForward()
{
    bForward = false;
}

