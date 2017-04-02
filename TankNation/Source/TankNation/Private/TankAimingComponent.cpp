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
	CurrentFiringGunState = EFiringGunState::ReloadingGun;

}

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::InitializeAiming(UTurret * TurretToSet, UTankBarrel * BarrelToSet,
	                                        UTankBarrel *GunToSet,UTankBarrel *GunToSet2)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
	Gun = GunToSet;
	Gun2 = GunToSet2;
}

void UTankAimingComponent::TickComponent(
	                                     float DeltaTime,
	                                     enum ELevelTick TickType,
										 FActorComponentTickFunction *ThisTickFunction
                                        )
{
	SetBarrelState();
	SetGunState();
	


}

void UTankAimingComponent::SetBarrelState()
{
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

void UTankAimingComponent::SetGunState()
{
	//Out of Ammo

	if (firingGunLeft <= 0)
	{
		CurrentFiringGunState = EFiringGunState::OutOfAmmoGun;
	}
	else if ((GetWorld()->GetTimeSeconds() - LastFireGunTime) < GunReloadTimeInSeconds)
	{
		CurrentFiringGunState = EFiringGunState::ReloadingGun;
	}
	else if (IsBarrelMoving())
	{
		CurrentFiringGunState = EFiringGunState::AimingGun;
	}
	else
	{
		CurrentFiringGunState = EFiringGunState::LockedGun;
	}
}
int32 UTankAimingComponent::GetFiringCount() const
{
	return firingLeft;
}

int32 UTankAimingComponent::GetGunFiringCount() const
{
	return firingGunLeft;
}


EFiringState UTankAimingComponent::GetCurrentState() const
{
	return CurrentFiringState;
}

//get current gun firing state
EFiringGunState UTankAimingComponent ::GetCurrentGunState() const
{
	return CurrentFiringGunState;
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

	if(Gun)
	Gun->Elevate(DeltaRot.Pitch);
	if(Gun2)
	Gun2->Elevate(DeltaRot.Pitch);

	
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
		ProjectileObj->LaunchProjectile(firingSpeed, GetOwner());
		LastFireTime = GetWorld()->GetTimeSeconds();
		firingLeft--;
	}

}

void UTankAimingComponent::FireGun()
{

	if (CurrentFiringGunState == EFiringGunState::AimingGun ||
		CurrentFiringGunState == EFiringGunState::LockedGun)
	{
		if (!ensure(Gun)) return;
		if (!ensure(Gun2)) return;
		if (!ensure(Gunprojectile)) return;

		//Spawn a Gun Projectile at the location of socket
		auto ProjectileObj = GetWorld()->SpawnActor<AProjectile>(
			Gunprojectile,
			Gun->GetSocketLocation(FName("ProjectileGun")),
			Gun->GetSocketRotation(FName("ProjectileGun"))
			);
		ProjectileObj->LaunchProjectile(firingSpeedGun,GetOwner());
		

		ProjectileObj = GetWorld()->SpawnActor<AProjectile>(
			Gunprojectile,
			Gun2->GetSocketLocation(FName("ProjectileGun")),
			Gun2->GetSocketRotation(FName("ProjectileGun"))
			);
		ProjectileObj->LaunchProjectile(firingSpeedGun,GetOwner());
		   LastFireGunTime = GetWorld()->GetTimeSeconds();
		   firingGunLeft-=2;


	}

}
