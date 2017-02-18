// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#pragma once

#include "Components/StaticMeshComponent.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision", "Lighting"))
class TANKNATION_API UTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	//-1 is Max download and +1 is max up Rotation
	void Azimuth(float RelativeSpeed);

private:
	//Maximum rotation speed of barrel
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 30.f;



};
