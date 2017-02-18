// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#include "TankNation.h"
#include "TankBarrel.h"
#include "Turret.h"
#include "TankAimingComponent.h"
#include "Tank.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	AimingComponent->SetBarrelReference(BarrelToSet);
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
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f : Tank Firing on duty"), Time)
}