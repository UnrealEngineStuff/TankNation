// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#include "TankNation.h"
#include "TankBarrel.h"
#include "Turret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel*BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTurret*TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation,float firingSpeed)
{
	if (!Barrel) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Cant Find Barrel "));
		return;
	}

	FVector OutTossVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this, OutTossVelocity, StartLocation,
		HitLocation, firingSpeed,false,0,0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if(bHaveAimSolution)
	{
		auto AimDirection = OutTossVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		//RotateBarrelTowards(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f : Aim Solution found"), Time)
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Error, TEXT("%f : Aim Solution Not found"), Time)
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Calculate Difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRot = AimAsRotator - BarrelRotator;
	//Move Barrel To the desired Location

	//it would matter if it is gretare than +1 or -1
	//it wll be clamped value greater than -1 will become -1
	Barrel->Elevate(DeltaRot.Pitch);
	// Fire when Ready 
}

void UTankAimingComponent::RotateTurret(FVector AimDirection)
{
	//Calculate Difference between current barrel rotation and AimDirection
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRot = AimAsRotator - TurretRotator;
	//Move Barrel To the desired Location

	//it would matter if it is greater than +1 or -1
	//it wll be clamped value greater than -1 will become -1
	Turret->Azimuth(DeltaRot.Yaw);
	// Fire when Ready 
}