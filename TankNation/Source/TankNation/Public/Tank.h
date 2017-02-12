// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#pragma once


#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "Tank.generated.h"    //No include below this 

class UTankBarrel;
UCLASS()
class TANKNATION_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable,Category = Setup)
	void SetBarrelReference(UTankBarrel*BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UStaticMeshComponent*BarrelToSet);


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
	float firingSpeed = 100000;

	
	
};
