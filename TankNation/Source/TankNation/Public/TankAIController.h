// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#pragma once


#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */

UCLASS()
class TANKNATION_API ATankAIController : public AAIController
{
	GENERATED_BODY()


private:	

		virtual void BeginPlay() override;

		virtual void Tick(float DeltaTime) override;


		UPROPERTY(EditAnywhere,Category = "AI")
		float AcceptanceRadius=1000.f;
	

};
