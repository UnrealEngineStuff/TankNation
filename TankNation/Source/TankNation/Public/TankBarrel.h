// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Tank Barrel /Gun 
 */
UCLASS(meta = (BlueprintSpawnableComponent))//,hidecategories=("Collision","Lighting"))
class TANKNATION_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	//-1 is Max download and +1 is max up Movement
	void Elevate(float RelativeSpeed);

private:
	//Maximum rotation speed of barrel
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 20.f;

	//Maximum Elevation of barrel
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 40.f;
	
	//Minimum Elevation of barrel
	UPROPERTY(EditAnywhere, Category = Setup)
    float MinElevationDegrees = 0.f;

	
};
