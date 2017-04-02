// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"    //No include below this 


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathEvent);

UCLASS()
class TANKNATION_API ATank : public APawn
{
	GENERATED_BODY()

public:
	//BLueprint cant change anything
	//it has no execution pin
	UFUNCTION(BlueprintPure, Category = "Setup")
	float GetHealth() const;

	FDeathEvent OnDeath;


private:
	// Sets default values for this pawn's properties
	ATank();


	//Called by then engine when projectile hit in range
	//Function to take Damage
	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const &DamageEvent,
		class  AController *EventInstigator,
		AActor*DamageCauser
	) override;



	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Health")
	int32 StartingHealth = 100;

	//Current Health of Tank
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;
	
};
