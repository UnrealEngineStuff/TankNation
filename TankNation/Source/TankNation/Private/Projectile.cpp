// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#include "TankNation.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	ProjectileMovement->bAutoActivate = false;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AProjectile::LaunchProjectile(float Speed)
{
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f : Projectile firing at speed %f"), Time,Speed);
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector*Speed);
	ProjectileMovement->Activate();
}