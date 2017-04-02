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
	Locked,
	OutOfAmmo,
};

UENUM()
enum class EFiringGunState :uint8
{
	ReloadingGun,
	AimingGun,
	LockedGun,
	OutOfAmmoGun
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

	//Called when fire key is pressed
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void FireGun();

	//INitialize Gun and Turret
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitializeAiming(UTurret * Turret, UTankBarrel * BarrelToSet,UTankBarrel * GunToSet,UTankBarrel *GunToSet2);

	EFiringState GetCurrentState() const;

	EFiringGunState GetCurrentGunState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetFiringCount() const;


	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetGunFiringCount() const;

protected:
	//Stores Current Firing state used by BP
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	EFiringState CurrentFiringState;

	//Stores Current Firing state used by BP
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	EFiringGunState CurrentFiringGunState;

private:
	//Move the Barrel at the given Direction
	//And also Rotates turret
	void MoveBarrelTowards();

	virtual void TickComponent(float DeltaTime, 
		                       enum ELevelTick TickType, 
		                       FActorComponentTickFunction *ThisTickFunction) override;

	//returns true if the barrel is moving 
	//compares the barrel/Gun forward vector
	bool IsBarrelMoving();

	//Set state of Gun
	//Only 2 state required
	//Reloading and Outof ammo
	//Rest are borrowed from Barrel
	//Since Gun always Move with Barrel
	void SetGunState();

	//set State of Barrel
	void SetBarrelState();

	FVector CurrentAimDirection;

	virtual void BeginPlay() override;
	
    //Launch Speed of projectile
	UPROPERTY(EditAnywhere, Category = "Firing")
	float firingSpeed = 8000.f;

	//Launch Speed of Gun
	UPROPERTY(EditAnywhere, Category = "Firing")
	float firingSpeedGun = 20000.f;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTimeInSeconds = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float GunReloadTimeInSeconds = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Firing")
	int32 firingLeft = 3;

	UPROPERTY(EditAnywhere, Category = "Firing")
	int32 firingGunLeft = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> projectile;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> Gunprojectile;


	UTankBarrel *Barrel = nullptr;
	UTankBarrel *Gun = nullptr;
	UTankBarrel *Gun2 = nullptr;
	UTurret *Turret = nullptr;

	float LastFireTime = 0;
	float LastFireGunTime = 0;



};
