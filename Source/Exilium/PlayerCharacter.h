
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
#include "PlayerCharacter.generated.h"

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

UCLASS()
class EXILIUM_API APlayerCharacter : public ACharacter
{
    GENERATED_BODY()

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

    UPROPERTY(EditAnywhere)
        float currentSpeed = 600.0f;
    UPROPERTY(EditAnywhere)
        float sprintMultiplier = 2.0f;
    UPROPERTY(EditAnywhere)
        float crouchMultiplier = 0.5f;
    UPROPERTY(EditAnywhere)
        float interactionDistance = 200.0f;
    UPROPERTY(EditAnywhere)
        float _baseEyeHeight = 64.0f;
    UPROPERTY(EditAnywhere)
        float _capsuleHeight = 88.0f;
    UPROPERTY(EditAnywhere)
        float lighterIntensity = 1000.0f;
    UPROPERTY(EditAnywhere)
        float candleIntensity = 3000.0f;
    UPROPERTY(EditAnywhere)
        int itemType = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isLeaning = false;
    UPROPERTY(EditAnywhere)
		TArray<FString> Inventory;

    FCollisionQueryParams TraceParams;

	void CheckForInteractables();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
        UCameraComponent* FPSCameraComponent;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Mesh)
        USkeletalMeshComponent* FPSMesh;

    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
        UStaticMeshComponent* CharacterHands;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Light)
        UPointLightComponent* PlayerLight;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Sound)
        UAudioComponent* PlayerSound;

    UPROPERTY(EditAnywhere)
        TSubclassOf<UCameraShake> IdleShake;

    UPROPERTY(EditAnywhere)
        TSubclassOf<UCameraShake> WalkShake;

    UPROPERTY(EditAnywhere)
        TSubclassOf<UCameraShake> RunShake;

	//Audio for openDoorSound -- connected with blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		USoundBase* openDoorSound;

// Interactable
public:
	/** Cast a line trace to detect IInteractable object **/
	UFUNCTION(BlueprintCallable, Category = Interactable)
	bool LineTraceInteractable(float range, FHitResult& outHit);
};
