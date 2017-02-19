// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"    //No include below this 

class UTankBarrel;
class UTankAimingComponent;
class UTurret;
class AProjectile;

UCLASS()
class TANKNATION_API ATank : public APawn
{
	GENERATED_BODY()

public:


	UFUNCTION(BlueprintCallable,Category = Setup)
	void SetBarrelReference(UTankBarrel*BarrelToSet);

	//Turret To Set
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTurret*TurretToSet);

	void AimAt(FVector HitLocation);

	//Called when fire key is pressed
	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();



protected:
	UTankAimingComponent *AimingComponent=nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere,Category = Firing)
	float firingSpeed = 8000;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> projectile;


	UTankBarrel*Barrel = nullptr;
	
	
};
