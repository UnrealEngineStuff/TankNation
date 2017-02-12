// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#pragma once

#include "Tank.h"
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

		//************************************
		// Returns:   ATank* (Returns Tank as an Actor That is possessed my TankAIController  
		// Qualifier: const
		//************************************
		ATank* GetControlledTank() const;


		//************************************
		// Returns:   ATank*(Returns Player Tank )
		// Qualifier: const
		//************************************
		ATank* GetPlayerControlledTank() const;


	


};
