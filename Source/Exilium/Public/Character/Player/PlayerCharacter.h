
#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/DataTable.h"
#include "PlayerStat.h"
#include "Sound/SoundCue.h"
#include "Components/PostProcessComponent.h"
#include "SanityState.h"
#include "PlayerCharacter.generated.h"
class UPawnNoiseEmitterComponent;

USTRUCT(BlueprintType)
struct FCraftingInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ComponentID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ProductID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bDestroyItemA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bDestroyItemB;
};

USTRUCT(BlueprintType)
struct FInventoryItem : public FTableRowBase
{
	GENERATED_BODY()
public:
	FInventoryItem()
	{
		Name = FText::FromString("Item");
		Action = FText::FromString("Use");
		Description = FText::FromString("Please enter a description for the item");
		Value = 10;
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ItemID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class APickup> ItemPickup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Action;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Thumbnail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FCraftingInfo> CraftingCombinations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanBeUsed;

	bool operator==(const FInventoryItem& Item) const
	{
		if (ItemID == Item.ItemID)
		{
			return true;
		}
		return false;
	}
};

UCLASS(config = Game, hidecategories = ("CharacterMovement"))
class EXILIUM_API APlayerCharacter : public ACharacter
{
    GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UPawnNoiseEmitterComponent* NoiseEmitterComponent;

public:
    APlayerCharacter();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveForward(float _value);
    void MoveRight(float _value);
    void StartJump();
    void StopJump();
    void StartCrouch();
    void StopCrouch();
    void CrouchImplement(float DeltaTime);
    void StartSprint();
    void StopSprint();
    void StartForward();
    void StopForward();
    void CheckSprint();
    void CheckHeadBob();
	void CheckForInteractables();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool bForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool bCrouching;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool bSprinting;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	bool bLighter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	bool bOpenDoor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	bool bPickup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
	bool isLeaning;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float currentSpeed = 420.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float sprintMultiplier = 1.5f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float crouchMultiplier = 0.3f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float interactionDistance = 200.0f;
	// needed to store the value of the player's original height
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float _baseEyeHeight = 64.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float _capsuleHeight = 88.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float lighterIntensity = 1000.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float candleIntensity = 3000.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int itemType = 0;

	
	FCollisionQueryParams TraceParams;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
    UCameraComponent* FPSCameraComponent;
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Mesh)
    USkeletalMeshComponent* FPSMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	TSubclassOf<UAudioComponent> ItemSound;
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Sound)
    UAudioComponent* PlayerSound;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UCameraShake> IdleShake;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UCameraShake> WalkShake;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UCameraShake> RunShake;
	

// Interactable
public:
	/** Cast a line trace to detect IInteractable object **/
	UFUNCTION(BlueprintCallable, Category = Interactable)
	bool LineTraceInteractable(float range, FHitResult& outHit);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Sanity)
		bool IsPlayerDangerChaseBGM = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Sanity)
		bool ContinuePlayerDangerChaseBGM = false;

	UFUNCTION(BlueprintImplementableEvent, Category = Sanity)
		void PlayDangerChaseBGM();
};
