// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"    //No include below this 



UCLASS()
class TANKNATION_API ATank : public APawn
{
	GENERATED_BODY()


	//Called by then engine when projectile hit in range
	//Function to take Damage
	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const &DamageEvent,
		class  AController *EventInstigator,
		AActor*DamageCauser
	) override;



private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 StartingHealth = 100;

	//Current Health of Tank
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartingHealth;
	
};
