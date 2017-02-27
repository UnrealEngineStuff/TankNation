// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKNATION_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
	
public:

	UFUNCTION(BlueprintCallable,Category = "Movement")
	void IntendMoveForward(float Value);

	UFUNCTION(BlueprintCallable, Category = "Movement")
    void IntendMoveRight(float Value);
	
	//Tracks To Set
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTrack * LeftTrack, UTankTrack * RightTrack);

private:
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	class UTankTrack*LeftTrack = nullptr;
	class UTankTrack*RightTrack = nullptr;


};
