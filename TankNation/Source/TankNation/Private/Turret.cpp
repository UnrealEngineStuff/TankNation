// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#include "TankNation.h"
#include "Turret.h"



void UTurret::Azimuth(float RelativeSpeed)
{
	//Moving The barrel
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto AzimuthChange = RelativeSpeed*MaxDegreesPerSecond*GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + AzimuthChange;
	SetRelativeRotation(FRotator(0,Rotation,0));
}



