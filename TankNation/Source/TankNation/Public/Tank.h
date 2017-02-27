// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"    //No include below this 


class UTankAimingComponent;
class UTankTrack;
class UTurret;
class UTankBarrel;
class AProjectile;


UCLASS()
class TANKNATION_API ATank : public APawn
{
	GENERATED_BODY()

public:


	void AimAt(FVector HitLocation);

	//Called when fire key is pressed
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();



protected:

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;


	UPROPERTY(EditAnywhere,Category = "Firing")
	float firingSpeed = 8000;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> projectile;

	UTankBarrel*Barrel = nullptr;


	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTimeInSeconds = 0.5f;

	float LastFireTime = 0;
	
	
};
