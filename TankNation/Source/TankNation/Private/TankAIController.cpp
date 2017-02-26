// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#include "TankNation.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	AITank = Cast<ATank>(GetPawn());

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	if (AITank)
	{
		MoveToActor(PlayerTank, AcceptanceRadius);
		if (PlayerTank)
		{
			//Aim towards the player
			AITank->AimAt(PlayerTank->GetActorLocation());
			//Fire if Ready
			AITank->Fire();
		}
	}
}
