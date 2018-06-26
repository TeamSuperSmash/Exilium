
#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraShake.h"
#include "HeadBob_Walk.generated.h"

UCLASS()
class EXILIUM_API UHeadBob_Walk : public UCameraShake
{
    GENERATED_BODY()

public:
    UHeadBob_Walk();
	
    UPROPERTY(EditAnywhere)
        float _OscillationDuration = 0.2f;

    UPROPERTY(EditAnywhere)
        float _OscillationBlendInTime = 0.1f;

    UPROPERTY(EditAnywhere)
        float _OscillationBlendOutTime = 0.2f;

    UPROPERTY(EditAnywhere)
        float _RotOscillationPitchAmplitude = 0.3f;

    UPROPERTY(EditAnywhere)
        float _RotOscillationPitchFrequency = 12.0f;

    UPROPERTY(EditAnywhere)
        float _RotOscillationYawAmplitude = 0.3f;

    UPROPERTY(EditAnywhere)
        float _RotOscillationYawFrequency = 6.0f;

    UPROPERTY(EditAnywhere)
        float _RotOscillationRollAmplitude = 0.2f;

    UPROPERTY(EditAnywhere)
        float _RotOscillationRollFrequency = 3.0f;

    UPROPERTY(EditAnywhere)
        float _LocOscillationZAmplitude = 0.6f;

    UPROPERTY(EditAnywhere)
        float _LocOscillationZFrequency = 12.0f;
};
