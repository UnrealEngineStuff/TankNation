// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#include "TankNation.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankTrack.h"
#include "TankBarrel.h"
#include "Projectile.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); // If we donont called Begin Play then BeginPlay of Blueprint 
	                    //will not be called
	AimingComponent = FindComponentByClass<UTankAimingComponent>();
}


//TODO We dont need this
//Remove and move to Aiming Componenet
void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(AimingComponent)) return;
	
	AimingComponent->AimAt(HitLocation, firingSpeed);
}

//TODO We dont need this
//Remove and move to Aiming Componenet
void ATank::Fire()
{
	if (!ensure(Barrel)) return;
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

