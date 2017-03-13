// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#include "TankNation.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"

//Depends on movement Componenet via pathfinding 

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();


}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());
	auto AITank =(GetPawn());
	if (!ensure(AITank) || !ensure(PlayerTank)) return;

	MoveToActor(PlayerTank, AcceptanceRadius);
	//Aim towards the player
	UTankAimingComponent *AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) return;
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	//Fire only when locked
	if(AimingComponent->GetCurrentState() == EFiringState::Locked)
	AimingComponent->Fire();
		
}
