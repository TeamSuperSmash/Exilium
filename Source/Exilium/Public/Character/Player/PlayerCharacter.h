
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

// "BlueprintType" is essential to include
UENUM(BlueprintType)
enum class ESanityState : uint8
{
	SANITY_LEVEL_0		UMETA(DisplayName = "SANITY_LEVEL_0"),
	SANITY_LEVEL_1		UMETA(DisplayName = "SANITY_LEVEL_1"),
	SANITY_LEVEL_2		UMETA(DisplayName = "SANITY_LEVEL_2"),
	SANITY_LEVEL_3		UMETA(DisplayName = "SANITY_LEVEL_3")
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
    void HoldLighter();
    void HoldCandle();
    void HoldMusicBox();
    void HoldBareHand();
    void ActivateItem();
    void DeActivateItem();
    void CheckSprint();
    void CheckHeadBob();
	void CheckForInteractables();
	void CheckSanityLevel();
	void UpdatePlayerState(float deltaTime);

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

	//sanity stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sanity)
	float currentSanity = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maximumSanity = 90.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float minimumSanity = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float sanityIncrementDelay = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float sanityThresholdGap = 30.0f;
	//! sanity threshold
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float sanityThreshold0 = 30.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float sanityThreshold1 = 60.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float sanityThreshold2 = 90.0f;

	//! sanity state
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sanity)
	ESanityState SanityState;

	//! sanity counter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sanity)
	float fogCounter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sanity)
	float fogTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sanity)
	float lookTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sanity)
	float lookDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sanity)
	float stayDuration;
	
	//player state
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	EPlayerState currentState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	EPlayerState previousState;

	
	FCollisionQueryParams TraceParams;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
    UCameraComponent* FPSCameraComponent;
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Mesh)
    USkeletalMeshComponent* FPSMesh;
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Light)
    UPointLightComponent* PlayerLight;
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

	//Audio for openDoorSound -- connected with blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* openDoorSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* walkingSound;

	//Post processing 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post processing")
	UPostProcessComponent* postComp;
	//! post process material
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post processing")
	UMaterialInstance* sanityMat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post processing")
	UMaterialInstanceDynamic* sanityDMI;
	

// Interactable
public:
	/** Cast a line trace to detect IInteractable object **/
	UFUNCTION(BlueprintCallable, Category = Interactable)
	bool LineTraceInteractable(float range, FHitResult& outHit);

	UFUNCTION(BlueprintCallable, Category = Sanity)
	void CheckValidFogState();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Sanity)
		bool IsPlayerDangerChaseBGM = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Sanity)
		bool ContinuePlayerDangerChaseBGM = false;

	UFUNCTION(BlueprintImplementableEvent, Category = Sanity)
		void PlayDangerChaseBGM();
};