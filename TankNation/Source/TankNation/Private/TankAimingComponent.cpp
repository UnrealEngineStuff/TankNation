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
	LastFireTime = FPlatformTime::Seconds();
}
void UTankAimingComponent::TickComponent(float DeltaTime,
	                                     enum ELevelTick TickType,
										 FActorComponentTickFunction *ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
		CurrentFiringState = EFiringState::Reloading;
	else if (IsBarrelMoving())
	{
		CurrentFiringState = EFiringState::Aiming;
	}
	else
		CurrentFiringState = EFiringState::Locked;
}
void UTankAimingComponent::InitializeAiming(UTurret * TurretToSet, UTankBarrel * Gun)
{
	Barrel = Gun;
	Turret = TurretToSet;
}

EFiringState UTankAimingComponent::GetCurrentState() const
{
	return CurrentFiringState;
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
		CurrentAimDirection = OutTossVelocity.GetSafeNormal();
		MoveBarrelTowards();
		auto Time = GetWorld()->GetTimeSeconds();
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto forwardVector = Barrel->GetForwardVector().GetSafeNormal();
	UE_LOG(LogTemp, Warning, TEXT("IsBarrelMoving Forward Vector :%s  CurrentAimDirection :%s"), *forwardVector.ToString(), *CurrentAimDirection.ToString());
	return !forwardVector.Equals(CurrentAimDirection,0.001);
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
		if (DeltaRot.Yaw > 180.f)
		{
			DeltaRot.Yaw = 180.f - (DeltaRot.Yaw);
		}
		else
		{
			DeltaRot.Yaw =  180 + DeltaRot.Yaw;
			DeltaRot.Yaw = FMath::Abs(DeltaRot.Yaw);
		}
	}


	Turret->Azimuth(DeltaRot.Yaw);


}


void UTankAimingComponent::Fire()
{

	if (CurrentFiringState != EFiringState::Reloading)
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
		LastFireTime = FPlatformTime::Seconds();
	}

}