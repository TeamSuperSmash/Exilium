
#include "HeadBob_Run.h"

UHeadBob_Run::UHeadBob_Run()
{
    bSingleInstance = true;

    OscillationDuration = _OscillationDuration;
    OscillationBlendInTime = _OscillationBlendInTime;
    OscillationBlendOutTime = _OscillationBlendOutTime;

    RotOscillation.Pitch.Amplitude = _RotOscillationPitchAmplitude;
    RotOscillation.Pitch.Frequency = _RotOscillationPitchFrequency;

    RotOscillation.Yaw.Amplitude = _RotOscillationYawAmplitude;
    RotOscillation.Yaw.Frequency = _RotOscillationYawFrequency;

    RotOscillation.Roll.Amplitude = _RotOscillationRollAmplitude;
    RotOscillation.Roll.Frequency = _RotOscillationRollFrequency;

    LocOscillation.Z.Amplitude = _LocOscillationZAmplitude;
    LocOscillation.Z.Frequency = _LocOscillationZFrequency;
};


