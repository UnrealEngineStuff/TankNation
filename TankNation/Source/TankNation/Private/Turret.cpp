// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#include "TankNation.h"
#include "Turret.h"



void UTurret::Azimuth(float RelativeSpeed)
{
	//Moving The barrel
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto AzimuthChange = RelativeSpeed*MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;
	UE_LOG(LogTemp, Warning, TEXT("This is Relative change %f "), AzimuthChange)
	auto RawNewAzimuth = RelativeRotation.Yaw + AzimuthChange;

	//auto ProcessedYaw = FMath::ClampAngle(RawNewAzimuth, 0,360);
	SetRelativeRotation(FRotator(0,RawNewAzimuth,0));
}



