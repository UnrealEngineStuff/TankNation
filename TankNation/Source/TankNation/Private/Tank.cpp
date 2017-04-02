// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#include "TankNation.h"
#include "Tank.h"



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
	CurrentHealth = StartingHealth;
}



float ATank::GetHealth() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent,
	                    AController * EventInstigator, AActor * DamageCauser)
{
	//We want health in integers
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);

	int32 ActualDamage = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);
	
	if (CurrentHealth <= 0)
	{

		OnDeath.Broadcast();

		return ActualDamage;
	}

	CurrentHealth -= ActualDamage;
	return ActualDamage;
}



