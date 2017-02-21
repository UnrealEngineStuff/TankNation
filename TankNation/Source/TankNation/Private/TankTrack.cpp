// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#include "TankNation.h"
#include "TankTrack.h"


void UTankTrack:: SetThrottle(float Value)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s Tank moving At %f"),*Name ,Value);

	//TODO clamp Throttle values
}

