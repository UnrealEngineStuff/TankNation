// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


//Enum for firing State
//this enables UE4 header tool to know its enum 
//and if wanted we can display in editor

UENUM()  
enum class EFiringState :uint8
{
	Reloading,
	Aiming,
	Locked
};

//Forward Declarations
class UTankBarrel;
class UTurret;
class AProjectile;

//Process on Tank Barrel Useful for Aiming
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKNATION_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	
	//Aim at Location
	void AimAt(FVector HitLocation);
	
	//Called when fire key is pressed
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();


	//INitialize Gun and Turret
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitializeAiming(UTurret * Turret, UTankBarrel * Gun);

protected:
	//Stores Current Firing state used by BP
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	EFiringState CurrentFiringState;

private:
	//Move the Barrel at the given Direction
	//And also Rotates turret
	void MoveBarrelTowards(FVector AimDirection);
	
    //Launch Speed of projectile
	UPROPERTY(EditAnywhere, Category = "Firing")
	float firingSpeed = 8000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> projectile;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTimeInSeconds = 0.5f;

	UTankBarrel *Barrel = nullptr;
	UTurret *Turret = nullptr;

	float LastFireTime = 0;

};
