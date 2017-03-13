// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank Track is used to make tank move with the force
 */
UCLASS(meta = (BlueprintSpawnableComponent))//,hidecategories=("Collision","Lighting"))
class TANKNATION_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	//Sets Throttle -1 ,+ 1
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetThrottle(float Value);
   
	//Maximum Force Per Track
	UPROPERTY(EditAnywhere,Category = "Movement")
	float MaxForcePerTrack = 400000;  // Mass x Acceleration
	
private:
	UTankTrack();

	virtual void BeginPlay() override;

	void ApplySideWaysForce();

	UFUNCTION()
		void OnHit(UPrimitiveComponent*HitComponent, AActor* OtherActor,
			UPrimitiveComponent*OtherComponent, FVector NormalImpulse,
			const FHitResult&Hit);

	void DriveTrack();

	float CurrentThrottle = 0.f;

	
};
