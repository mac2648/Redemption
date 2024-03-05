#include "Math.h"

FRotator Math::InterpConstantTo(FRotator Current, FRotator Target, float DeltaTime, float Speed)
{
	double NewRotationPitch = FMath::FInterpConstantTo(Current.Pitch, Target.Pitch, DeltaTime, Speed);
	double NewRotationYaw = FMath::FInterpConstantTo(Current.Yaw, Target.Yaw, DeltaTime, Speed);
	double NewRotationRoll = FMath::FInterpConstantTo(Current.Roll, Target.Roll, DeltaTime, Speed);

	FRotator NewRotation = FRotator::TRotator(NewRotationPitch, NewRotationYaw, NewRotationRoll);

	return NewRotation;
}