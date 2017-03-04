// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#include "TankNation.h"
#include "Tank.h"
#include "TankAIController.h"

//Depends on movement Componenet via pathfinding 

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	AITank = Cast<ATank>(GetPawn());

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!ensure(AITank&&PlayerTank)) return;
	MoveToActor(PlayerTank, AcceptanceRadius);
	//Aim towards the playe
	AITank->AimAt(PlayerTank->GetActorLocation());
	//Fire if Ready
	AITank->Fire();
		
}
