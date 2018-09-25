//// Fill out your copyright notice in the Description page of Project Settings.
//
//#include "PlayerMotionComponent.h"
//
//// Sets default values for this component's properties
//UPlayerMotionComponent::UPlayerMotionComponent()
//{
//	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
//	// off to improve performance if you don't need them.
//	PrimaryComponentTick.bCanEverTick = true;
//
//	// ...
//	pawn = Cast<APlayerCharacter>(GetOwner());
//	camera = pawn->FPSCameraComponent;
//	capsuleCol = pawn->GetCapsuleComponent();
//
//	baseEyeHeight = camera->GetRelativeTransform().GetLocation().Z;
//	baseColliderHeight = capsuleCol->GetUnscaledCapsuleHalfHeight();
//}
//
//
//// Called when the game starts
//void UPlayerMotionComponent::BeginPlay()
//{
//	Super::BeginPlay();
//
//	// ...
//	
//}
//
//
//// Called every frame
//void UPlayerMotionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//	OnCrouch(DeltaTime);
//}
//
//void UPlayerMotionComponent::Move(FVector2D value)
//{
//	//Prevent player from slowing down when camera pointing upwards/downwards
//	const FRotator YawOnlyRotation = FRotator(0.0f, pawn->GetControlRotation().Yaw, 0.0f);
//	const FVector DirectionY = FRotationMatrix(YawOnlyRotation).GetScaledAxis(EAxis::X);
//	pawn->AddMovementInput(DirectionY, value.Y);
//
//	const FVector DirectionX = FRotationMatrix(pawn->GetControlRotation()).GetScaledAxis(EAxis::Y);
//	pawn->AddMovementInput(DirectionX, value.X);
//
//	//UGameplayStatics::PlaySoundAtLocation(this, walkingSound, GetActorLocation());
//}
//
//void UPlayerMotionComponent::OnCrouch(float deltaTime)
//{
//	float targetEyeHeight = baseEyeHeight;
//	float targetColliderHeight = baseColliderHeight;
//
//	if (motionState == EPlayerMotionState::Crouching)
//	{
//		targetEyeHeight = crouchedEyeHeight;
//		targetColliderHeight = crouchedColliderHeight;
//	}
//
//	if (pawn->Controller != NULL)
//	{
//		currentEyeHeight = FMath::FInterpTo(currentEyeHeight, targetEyeHeight, deltaTime, crouchSpeed);
//		currentColliderHeight = FMath::FInterpTo(currentColliderHeight, targetColliderHeight, deltaTime, crouchSpeed);
//
//		capsuleCol->SetCapsuleHalfHeight(currentColliderHeight, true);
//
//		// <!> Should not be needed when pivoting the player at the foot
//		// Dist and DeltaMovCaps are used for the interpolation value added to RelativeLocation.Z
//		const float distance = targetColliderHeight - currentColliderHeight;
//		const float deltaMovCaps = distance * FMath::Clamp<float>(deltaTime * crouchSpeed, 0.0f, 1.0f);
//		const FVector newLocCapsule = capsuleCol->RelativeLocation + FVector(0.0f, 0.0f, deltaMovCaps);
//
//		capsuleCol->SetRelativeLocation(newLocCapsule, true);
//
//		// Move Camera
//		const FVector newLocCamera = 
//			(camera->RelativeLocation * FVector(1.0f, 1.0f, 0.0f)) +
//			FVector(0.0f, 0.0f, targetEyeHeight);
//
//		camera->SetRelativeLocation(newLocCamera);
//	}
//}
