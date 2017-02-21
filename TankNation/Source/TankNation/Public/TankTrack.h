// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank Track is used to make tank move with the force
 */
UCLASS(meta = (BlueprintSpawnableComponent))//,hidecategories=("Collision","Lighting"))
class TANKNATION_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	//Sets Throttle -1 ,+ 1
	UFUNCTION(BlueprintCallable,Category = Input)
	void SetThrottle(float Value);
	
	
};
