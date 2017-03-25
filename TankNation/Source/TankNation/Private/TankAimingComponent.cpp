 // Tank Nation Game Developed By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#include "TankNation.h"
#include "TankBarrel.h"
#include "Turret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	CurrentFiringState = EFiringState::Reloading;

}

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::InitializeAiming(UTurret * TurretToSet, UTankBarrel * Gun)
{
	Barrel = Gun;
	Turret = TurretToSet;
}

void UTankAimingComponent::TickComponent(
	                                     float DeltaTime,
	                                     enum ELevelTick TickType,
										 FActorComponentTickFunction *ThisTickFunction
                                        )
{
	//Out of Ammo
	if (firingLeft <= 0)
	{
		CurrentFiringState = EFiringState::OutOfAmmo;
	}

	else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		CurrentFiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		CurrentFiringState = EFiringState::Aiming;
	}
	else
	{
		CurrentFiringState = EFiringState::Locked;
	}
}
int32 UTankAimingComponent::GetFiringCount() const
{
	return firingLeft;
}


EFiringState UTankAimingComponent::GetCurrentState() const
{
	return CurrentFiringState;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto forwardVector = Barrel->GetForwardVector();
	return !forwardVector.Equals(CurrentAimDirection, 0.01);
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel))  return;

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
		CurrentAimDirection = OutTossVelocity.GetSafeNormal();
		MoveBarrelTowards();
	}

	//Do nothing if no solution found
}


void UTankAimingComponent::MoveBarrelTowards()
{
	if (!ensure(Barrel) ||!ensure(Turret)) return;
	
	//Calculate Difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = CurrentAimDirection.Rotation();
	auto DeltaRot = AimAsRotator - BarrelRotator;
	//Move Barrel To the desired Location

	//it would matter if it is gretare than +1 or -1
	//it wll be clamped value greater than -1 will become -1
	Barrel->Elevate(DeltaRot.Pitch);

	
	//TODO make sure that it takes smallest route
	if (FMath::Abs(DeltaRot.Yaw) > 180.f)
	{
		Turret->Azimuth(-DeltaRot.Yaw);
	}
	else
	{
		Turret->Azimuth(DeltaRot.Yaw);
	}

}


void UTankAimingComponent::Fire()
{

	if (CurrentFiringState == EFiringState::Aiming ||
		CurrentFiringState == EFiringState::Locked)
	{
		if (!ensure(Barrel)) return;
		if (!ensure(projectile)) return;

		//Spawn a projectile at the location of socket
		auto ProjectileObj = GetWorld()->SpawnActor<AProjectile>(
			projectile,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		ProjectileObj->LaunchProjectile(firingSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
		firingLeft--;
	}

}

