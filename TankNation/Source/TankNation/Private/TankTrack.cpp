// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#include "TankNation.h"
#include "TankTrack.h"


void UTankTrack:: SetThrottle(float Value)
{

	//TODO clamp Throttle values
	auto ForceApplied = GetForwardVector()*Value*MaxForcePerTrack;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}

