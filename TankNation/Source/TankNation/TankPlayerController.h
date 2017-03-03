// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * Responsible for making how player's aim
 */
class ATank;
class UTankAimingComponent;

UCLASS()
class TANKNATION_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;




	//************************************
	// Method:    AimAtCrossover
	// Note:      Moves Gun at the Crossover point
	//            so that we can shoot at the desired location
	//************************************
	void AimAtCrossover();

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent *AimComponenetRef);

private:

	//************************************
	// Note:      Function updates HitLocation .The location at which crosshair
	//            is aiming.If it hits Nothing like sky then function returns false
	//            else true
	// Parameter: FVector & HitLocation
	//************************************
	bool GetObjectHitLocation(FVector & HitLocation) const;

	//************************************
	// Method:    GetLookDirection
	// Note:   Projects Screen Cursor to world
	// Parameter: FVector2D ScreenLocation
	// Parameter: FVector & LookDirection
	//************************************
	bool GetLookingDirection(FVector2D ScreenLocation, FVector & LookDirection) const;

	//************************************
	// Method:    GetLookVectorHitLocation
	// Note:      Returns the HIt object location.
	// Parameter: LookDirection-Direction in which to Look
	//            HitDirection- Location of object hit
	// returns    true if Successfully hit
	//            else false
	//************************************
	bool GetHitObjectLocation(FVector &LookDirection, FVector &HitDirection ) const;

	//Location of Crosshair in X direction
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5f;
	
	//Location of Cross hair in Y direction
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333f;


	//Location of Cross hair in Y direction
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.f;

	
	
};
