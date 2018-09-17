
#include "PlayerCharacter.h"
#include "Exilium.h"
#include "GameplayController.h"
#include "Interactable.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PawnNoiseEmitterComponent.h"

APlayerCharacter::APlayerCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

    _baseEyeHeight = BaseEyeHeight;
    _capsuleHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();

    GetCharacterMovement()->MaxWalkSpeed = currentSpeed;
    GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

    FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FPSCameraComponent->SetupAttachment(GetCapsuleComponent());
    FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50 + BaseEyeHeight));
    FPSCameraComponent->bUsePawnControlRotation = true;
	
    FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
    FPSMesh->SetOnlyOwnerSee(true);
    FPSMesh->SetupAttachment(GetCapsuleComponent());
    FPSMesh->bCastDynamicShadow = false;
    FPSMesh->CastShadow = false;

    PlayerSound = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound"));
    PlayerSound->SetupAttachment(GetCapsuleComponent());
    PlayerSound->bAutoActivate = false;

    TraceParams = FCollisionQueryParams(FName(TEXT("Trace")), true, this);

	NoiseEmitterComponent = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitterComponent"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("Starting PlayerCharacter"));
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    CrouchImplement(DeltaTime);
    CheckSprint();
    CheckHeadBob();
	CheckForInteractables();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

    PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::StartCrouch);
    PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APlayerCharacter::StopCrouch);

    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::StartSprint);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::StopSprint);

    PlayerInputComponent->BindAction("ForwardKey", IE_Pressed, this, &APlayerCharacter::StartForward);
    PlayerInputComponent->BindAction("ForwardKey", IE_Released, this, &APlayerCharacter::StopForward);
}

void APlayerCharacter::MoveForward(float _value)
{
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
}

void APlayerCharacter::StopCrouch()
{
    bCrouching = false;
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

void APlayerCharacter::CheckForInteractables()
{
	FHitResult HitResult;

	FVector Loc;
	FRotator Rot;
	GetController()->GetPlayerViewPoint(Loc, Rot);

	FVector Start = Loc;
	FVector End = Start + (Rot.Vector() * 300.0f);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	AGameplayController* Controller = Cast<AGameplayController>(GetController());

	if (!Controller)
	{
		return;
	}

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams))
	{
		// Check the item we hit is an interactable item.
		if(HitResult.GetActor()->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
		{
			//IInteractable* Interactable = Cast<IInteractable>(HitResult.GetActor());
			Controller->CurrentInteractable = HitResult.GetActor();
			return;
		}
	}
	// If did not hit anything, or hit unusable. Set current interactable to nullptr.
	Controller->CurrentInteractable = nullptr;
}

void APlayerCharacter::CrouchImplement(float DeltaTime)
{
    float TargetBaseEyeHeight = NULL;
    float TargetCapsuleSize = NULL;

    if (bCrouching)
    {
        TargetBaseEyeHeight = CrouchedEyeHeight;
        TargetCapsuleSize = GetCharacterMovement()->CrouchedHalfHeight;
    }
    else
    {
        TargetBaseEyeHeight = _baseEyeHeight;
        TargetCapsuleSize = _capsuleHeight;
    }

    if (Controller != NULL)
    {
        BaseEyeHeight = FMath::FInterpTo(BaseEyeHeight, TargetBaseEyeHeight, DeltaTime, 10.0f);

        GetCapsuleComponent()->SetCapsuleHalfHeight(FMath::FInterpTo
        (GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight(), TargetCapsuleSize, DeltaTime, 10.0f), true);

        // Dist and DeltaMovCaps are used for the interpolation value added to RelativeLocation.Z
        const float Dist = TargetCapsuleSize - GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
        const float DeltaMovCaps = Dist * FMath::Clamp<float>(DeltaTime * 10.0f, 0.0f, 1.0f);

        GetCapsuleComponent()->SetRelativeLocation(FVector(GetCapsuleComponent()->RelativeLocation.X,
            GetCapsuleComponent()->RelativeLocation.Y, (GetCapsuleComponent()->RelativeLocation.Z +
                DeltaMovCaps)), true);
    }
}

void APlayerCharacter::CheckSprint()
{
    if (bSprinting && bForward && !bCrouching)
    {
        GetCharacterMovement()->MaxWalkSpeed = currentSpeed * sprintMultiplier;
    }
    else if (bCrouching)
    {
        GetCharacterMovement()->MaxWalkSpeed = currentSpeed * crouchMultiplier;
    }
    else
    {
        GetCharacterMovement()->MaxWalkSpeed = currentSpeed;
    }
}

void APlayerCharacter::CheckHeadBob()
{
    if (!GetVelocity().IsZero() && !GetCharacterMovement()->IsFalling())
    {
        if (bSprinting && bForward && !bCrouching)
        {
            GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(RunShake, 1.0f);
        }
        else
        {
            GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(WalkShake, 1.0f);
        }
	}
	else if(GetVelocity().IsZero() && !GetCharacterMovement()->IsFalling())
	{
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(IdleShake, 1.0f);
	}
}

bool APlayerCharacter::LineTraceInteractable(float range, FHitResult& outHit)
{
	FHitResult hit;
	FVector startPoint = FPSCameraComponent->GetComponentLocation();
	FVector endPoint = startPoint + (FPSCameraComponent->GetForwardVector() * range);
	FCollisionQueryParams collisionParams;

	if (GetWorld()->LineTraceSingleByChannel(hit, startPoint, endPoint, ECC_Visibility, collisionParams))
	{
		if (hit.bBlockingHit)
		{
			if (UKismetSystemLibrary::DoesImplementInterface(hit.GetActor(), UInteractable::StaticClass()))
			{
				outHit = hit;
				return true;
			}
		}
	}

	return false;
}




