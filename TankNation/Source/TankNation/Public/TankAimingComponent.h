// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTurret;

//Process on Tank Barrel Useful for Aiming
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKNATION_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel*BarrelToSet);

	void SetTurretReference(UTurret*TurretToSet);

	//Aim at Location
	void AimAt(FVector HitLocation,float firingSpeed);

private:
	UTankBarrel *Barrel = nullptr;
	UTurret *Turret = nullptr;

	//Move the Barrel at the given Direction
	//And also Rotates turret
	void MoveBarrelTowards(FVector AimDirection);

};
