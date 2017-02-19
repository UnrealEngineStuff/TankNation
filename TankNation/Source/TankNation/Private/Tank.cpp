// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#include "TankNation.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Turret.h"
#include "TankBarrel.h"
#include "Projectile.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	

}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	if (BarrelToSet)
	{
		AimingComponent->SetBarrelReference(BarrelToSet);
		Barrel = BarrelToSet;
	}
}

void ATank::SetTurretReference(UTurret * TurretToSet)
{
	AimingComponent->SetTurretReference(TurretToSet);
}



// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	if (AimingComponent)
	{
		AimingComponent->AimAt(HitLocation,firingSpeed);
	}
}
void ATank::Fire()
{

    
	if (!Barrel) return;
	//Spawn a projectile at the location of socket
	auto ProjectileObj = GetWorld()->SpawnActor<AProjectile>(
						projectile,
						Barrel->GetSocketLocation(FName("Projectile")),
						Barrel->GetSocketRotation(FName("Projectile"))
						);
	ProjectileObj->LaunchProjectile(firingSpeed);
}