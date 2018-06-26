
#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraShake.h"
#include "HeadBob_Run.generated.h"

UCLASS()
class EXILIUM_API UHeadBob_Run : public UCameraShake
{
    GENERATED_BODY()

public:
    UHeadBob_Run();

    UPROPERTY(EditAnywhere)
        float _OscillationDuration = 0.2f;

    UPROPERTY(EditAnywhere)
        float _OscillationBlendInTime = 0.1f;

    UPROPERTY(EditAnywhere)
        float _OscillationBlendOutTime = 0.2f;

    UPROPERTY(EditAnywhere)
        float _RotOscillationPitchAmplitude = 0.5f;

    UPROPERTY(EditAnywhere)
        float _RotOscillationPitchFrequency = 17.0f;

    UPROPERTY(EditAnywhere)
        float _RotOscillationYawAmplitude = 0.5f;

    UPROPERTY(EditAnywhere)
        float _RotOscillationYawFrequency = 8.5f;

    UPROPERTY(EditAnywhere)
        float _RotOscillationRollAmplitude = 0.2f;

    UPROPERTY(EditAnywhere)
        float _RotOscillationRollFrequency = 4.75f;

    UPROPERTY(EditAnywhere)
        float _LocOscillationZAmplitude = 2.0f;

    UPROPERTY(EditAnywhere)
        float _LocOscillationZFrequency = 17.0f;
};      
