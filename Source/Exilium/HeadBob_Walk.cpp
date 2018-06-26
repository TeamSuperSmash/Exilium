
#include "HeadBob_Walk.h"

UHeadBob_Walk::UHeadBob_Walk()
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


