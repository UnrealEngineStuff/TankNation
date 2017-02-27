// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


//Enum for firing State
UENUM()  //this enables UE4 header tool to know its enum and if wanted we can display in editor
enum class EFiringState :uint8
{
	Reloading,
	Aiming,
	Locked
	
};

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

	//Aim at Location
	void AimAt(FVector HitLocation,float firingSpeed);

	//INitialize Gun and Turret
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitializeAiming(UTurret * Turret, UTankBarrel * Gun);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	EFiringState CurrentFiringState;

private:
	UTankBarrel *Barrel = nullptr;
	UTurret *Turret = nullptr;

	//Move the Barrel at the given Direction
	//And also Rotates turret
	void MoveBarrelTowards(FVector AimDirection);

};
