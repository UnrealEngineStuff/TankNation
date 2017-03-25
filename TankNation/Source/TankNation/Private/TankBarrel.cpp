// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#include "TankNation.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	//Moving The barrel
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed*MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch +	 ElevationChange;
	//auto ProcessedElevation = FMath::ClampAngle(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	auto ProcessedElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(ProcessedElevation, 0, 0));
}

