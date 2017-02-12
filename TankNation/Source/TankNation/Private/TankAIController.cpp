// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#include "TankNation.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto*TankAI = GetControlledTank();
	if (!TankAI)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot Find Tank possessed by TankAIController"))
	}

	auto *TankPlayer = GetPlayerControlledTank();
	if (!TankPlayer)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot Find Tank possessed by TankPlayer Controller Which is to be seen by TankAIController"))
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerControlledTank())
	{
		//TODO move Towards the player
		if (GetControlledTank())
		{
			//Aim towards the player
			GetControlledTank()->AimAt(GetPlayerControlledTank()->GetActorLocation());

			//Fire if Ready
		}
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerControlledTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

}
