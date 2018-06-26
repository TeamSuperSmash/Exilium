
#include "PlayerCharacter.h"
#include "Interact_Interface.h"
#include "Exilium.h"

APlayerCharacter::APlayerCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

    GetCharacterMovement()->MaxWalkSpeed = currentSpeed;

    GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

    FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FPSCameraComponent->SetupAttachment(GetCapsuleComponent());
    FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, cameraHeight));
    FPSCameraComponent->bUsePawnControlRotation = true;

    FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
    FPSMesh->SetOnlyOwnerSee(true);
    FPSMesh->SetupAttachment(FPSCameraComponent);
    FPSMesh->bCastDynamicShadow = false;
    FPSMesh->CastShadow = false;

    GetMesh()->SetOwnerNoSee(true);

    TraceParams = FCollisionQueryParams(FName(TEXT("Trace")), true, this);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
    if (GEngine)
    {
        //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Using PlayerCharacter!"));
    }

    UE_LOG(LogTemp, Warning, TEXT("Starting PlayerCharacter"));
}

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

    if (GetVelocity().X != 0.0f || GetVelocity().Y != 0.0f)
    {
        GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(WalkShake, 1.0f);
    }
    else if (GetVelocity().X != 0.0f || GetVelocity().Y != 0.0f && bSprinting)
    {
        GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(RunShake, 1.0f);
    }

    CheckFocusActor();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

    PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJump);

    PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::StartCrouch);
    PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APlayerCharacter::StopCrouch);

    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::StartSprint);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::StopSprint);

    PlayerInputComponent->BindAction("ForwardKey", IE_Pressed, this, &APlayerCharacter::StartForward);
    PlayerInputComponent->BindAction("ForwardKey", IE_Released, this, &APlayerCharacter::StopForward);

    PlayerInputComponent->BindAction("InteractKey", IE_Pressed, this, &APlayerCharacter::Interact);
}

void APlayerCharacter::MoveForward(float _value)
{
    //FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
    //AddMovementInput(Direction, _value);

    const FRotator YawOnlyRotation = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
    AddMovementInput(FRotationMatrix(YawOnlyRotation).GetUnitAxis(EAxis::X), _value);
}

void APlayerCharacter::MoveRight(float _value)
{
    FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
    AddMovementInput(Direction, _value);
}

#pragma region MoveBooleans
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
#pragma endregion

void APlayerCharacter::Interact()
{
    AActor* Interactable = FindActorInLOS();

    if (Interactable)
    {
        IInteract_Interface* Interface = Cast<IInteract_Interface>(Interactable);
        if (Interface)
        {
            Interface->Execute_OnInteract(Interactable, this);
        }
    }
}

void APlayerCharacter::CheckFocusActor()
{
    AActor* Interactable = FindActorInLOS();

    if (Interactable)
    {
        if (Interactable != FocusedActor)
        {
            if (FocusedActor)
            {
                IInteract_Interface* Interface = Cast<IInteract_Interface>(FocusedActor);
                if (Interface)
                {
                    Interface->Execute_EndFocus(FocusedActor);
                }
            }
            IInteract_Interface* Interface = Cast<IInteract_Interface>(Interactable);
            if (Interface)
            {
                Interface->Execute_StartFocus(Interactable);
            }
            FocusedActor = Interactable;
        }
    }
    else
    {
        if (FocusedActor)
        {
            IInteract_Interface* Interface = Cast<IInteract_Interface>(FocusedActor);
            if (Interface)
            {
                Interface->Execute_EndFocus(FocusedActor);
            }
        }
        FocusedActor = nullptr;
    }
}

AActor * APlayerCharacter::FindActorInLOS()
{
    if (!Controller)
    {
        return nullptr;
    }

    FVector Loc;
    FRotator Rot;
    FHitResult Hit(ForceInit);
    GetController()->GetPlayerViewPoint(Loc, Rot);

    FVector Start = Loc;
    FVector End = Start + (Rot.Vector() * interactionDistance);

    GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);

    return Hit.GetActor();
}



