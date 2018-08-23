
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

    GetMesh()->SetOwnerNoSee(true);

    PlayerLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
    PlayerLight->SetupAttachment(FPSMesh);
    PlayerLight->bVisible = false;

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
	currentState = EPlayerState::NONE;
	previousState = EPlayerState::NONE;
	//initialize sanity properties
	stayDuration = 60.0f;
	lookDuration = 5.0f;
	//initialize post processing Dynamic Material Instance
	TArray<UPostProcessComponent*> pcomps;
	GetComponents<UPostProcessComponent>(pcomps);
	postComp = pcomps[0];
	sanityDMI = UMaterialInstanceDynamic::Create(sanityMat, this);
	sanityDMI->SetScalarParameterValue("Strength", currentSanity/10.0f);
	FPostProcessVolumeProperties prop = postComp->GetProperties();
	//prop.Settings->AddBlendable(sanityDMI, 1.0f);

	if (sanityDMI->GetClass()->ImplementsInterface(UBlendableInterface::StaticClass()))
	{
		postComp->AddOrUpdateBlendable(TScriptInterface<IBlendableInterface>(sanityDMI), 1.0f);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    CrouchImplement(DeltaTime);
    CheckSprint();
    CheckHeadBob();
	CheckForInteractables();
	CheckSanityLevel();
	UpdatePlayerState(DeltaTime);
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

    PlayerInputComponent->BindAction("LeftMouse", IE_Pressed, this, &APlayerCharacter::ActivateItem);
}

void APlayerCharacter::MoveForward(float _value)
{
	const FRotator YawOnlyRotation = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
	AddMovementInput(FRotationMatrix(YawOnlyRotation).GetUnitAxis(EAxis::X), _value);

	UGameplayStatics::PlaySoundAtLocation(this, walkingSound, GetActorLocation());
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

void APlayerCharacter::HoldLighter()
{
    if (itemType != 1)
    {
        UE_LOG(LogTemp, Warning, TEXT("Currently holding lighter!"));

        DeActivateItem(); 
        itemType = 1;

		bLighter = true;

        PlayerLight->SetIntensity(lighterIntensity);
    }
}

void APlayerCharacter::HoldCandle()
{
    if (itemType != 2)
    {
        UE_LOG(LogTemp, Warning, TEXT("Currently holding candle!"));

        DeActivateItem();
        itemType = 2;

        PlayerLight->SetIntensity(candleIntensity);
    }
}

void APlayerCharacter::HoldMusicBox()
{
    if (itemType != 3)
    {
        UE_LOG(LogTemp, Warning, TEXT("Currently holding music box!"));

        DeActivateItem();
        itemType = 3;
    }
}

void APlayerCharacter::HoldBareHand()
{
    if (itemType != 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Currently holding bare hands!"));

        DeActivateItem();
        itemType = 0;
    }
}

void APlayerCharacter::ActivateItem()
{
    if (itemType == 1 || itemType == 2)
    {
        if (PlayerLight->bVisible)
        {
            PlayerLight->SetVisibility(false);
        }
        else
        {
            PlayerLight->SetVisibility(true);
        }
    }
    else if (itemType == 3)
    {
        if (PlayerSound->bIsActive)
        {
            PlayerSound->SetActive(false);
        }
        else
        {
            PlayerSound->SetActive(true);
        }
    }
}

void APlayerCharacter::DeActivateItem()
{
    PlayerLight->SetVisibility(false);
    PlayerSound->SetActive(false);

	bLighter = false;
	bOpenDoor = false;
	bPickup = false;
}

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

void APlayerCharacter::CheckSanityLevel()
{
	if (currentSanity >= sanityThreshold0 && currentSanity < sanityThreshold1)
	{
		SanityState = ESanityState::SANITY_LEVEL_1;
	}
	else if (currentSanity >= sanityThreshold1 && currentSanity < sanityThreshold2)
	{
		SanityState = ESanityState::SANITY_LEVEL_2;
	}
	else if (currentSanity >= sanityThreshold2)
	{
		SanityState = ESanityState::SANITY_LEVEL_3;
	}
	else if (currentSanity < sanityThreshold0)
	{
		SanityState = ESanityState::SANITY_LEVEL_0;
	}

	if (currentSanity > maximumSanity)
	{
		currentSanity = maximumSanity;
	}
	else if (currentSanity < minimumSanity)
	{
		currentSanity = minimumSanity;
	}
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

void APlayerCharacter::CheckValidFogState()
{
	if (currentState == EPlayerState::NONE || currentState == EPlayerState::INFOG)
	{
		currentState = EPlayerState::INFOG;
	}
}

void APlayerCharacter::UpdatePlayerState(float deltaTime)
{
	float strength = FMath::Lerp(0.0f, 0.09f, currentSanity / 90.0f);

	sanityDMI->SetScalarParameterValue("Strength", strength);
	if (currentState == EPlayerState::NONE)
	{
		if (fogCounter > 0)
		{
			fogTimer += deltaTime;
			if (fogTimer >= 1.0f)
			{
				fogTimer = 0;
				fogCounter--;
			}
		}
		if (lookDuration > 0)
		{
			lookDuration -= deltaTime;
		}
	}
	else if (currentState == EPlayerState::INFOG)
	{
		fogTimer += deltaTime;
		float curThreshold = (static_cast<int>(SanityState) * sanityThresholdGap) + sanityThresholdGap;
		float insanityIncrement = sanityThresholdGap / stayDuration;
		
		if (fogTimer >= 1.0f)
		{
			fogTimer = 0;
			fogCounter++;
			
			if (currentSanity + insanityIncrement < curThreshold)
			{
				currentSanity += insanityIncrement;
			}
		}
		
		if (fogCounter >= stayDuration)
		{
			fogCounter = 0;
			fogTimer = 0;
			previousState = EPlayerState::INFOG;
			currentState = EPlayerState::BREATHINGMINI;
		}
	}
	else if (currentState == EPlayerState::LOOKATMONSTER)
	{
		//! --monster cannot move fuction
		lookTimer += deltaTime;
		if (lookTimer >= lookDuration)
		{
			lookTimer = 0;
			//! --monster move toward function
			previousState = EPlayerState::LOOKATMONSTER;
			currentState = EPlayerState::BREATHINGMINI;
			//trigger breating mini game
		}
	}
	else if (currentState == EPlayerState::BREATHINGMINI)
	{
		currentSanity = (static_cast<int>(SanityState) * sanityThresholdGap) + sanityThresholdGap;
		currentState = previousState;
		
		//! --if success
		//! --change music
		//! --set sanity
		//! --set to previosState
		//! --else 
		//! --change music
		//currentState = EPlayerState::HEARTBEATMINI;
	}
	else if (currentState == EPlayerState::HEARTBEATMINI)
	{
		//lose
	}
}



