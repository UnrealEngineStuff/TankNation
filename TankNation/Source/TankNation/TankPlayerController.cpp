// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com


#include "TankNation.h"
#include "TankPlayerController.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
