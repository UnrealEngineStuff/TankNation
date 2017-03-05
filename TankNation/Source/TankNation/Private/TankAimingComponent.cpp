 // Tank Nation Game Developed By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#include "TankNation.h"
#include "TankBarrel.h"
#include "Turret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentFiringState = EFiringState::Aiming;

}

void UTankAimingComponent::InitializeAiming(UTurret * TurretToSet, UTankBarrel * Gun)
{
	Barrel = Gun;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel) || !ensure(Turret)) return;

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
		auto Time = GetWorld()->GetTimeSeconds();
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) ||!ensure(Turret)) return;
	
	//Calculate Difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRot = AimAsRotator - BarrelRotator;
	//Move Barrel To the desired Location

	//it would matter if it is gretare than +1 or -1
	//it wll be clamped value greater than -1 will become -1
	Barrel->Elevate(DeltaRot.Pitch);
	Turret->Azimuth(DeltaRot.Yaw);

}


void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel&&projectile)) return;
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (isReloaded)
	{
		//Spawn a projectile at the location of socket
		auto ProjectileObj = GetWorld()->SpawnActor<AProjectile>(
			projectile,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		ProjectileObj->LaunchProjectile(firingSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}

}