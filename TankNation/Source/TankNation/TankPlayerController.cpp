// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com



#include "TankNation.h"
#include "Tank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto*obj = GetControlledTank();

	if (obj == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot Find Tank possessed by TankPlayerController"))
	}
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrossover();

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrossover()
{
	//If we Didn't Got a Tank THen Return
	if (!GetControlledTank()) { return; }

	FVector HitLocation(0,0,0);

	//Get POsition of any object that is in direction of Tank Crossover
	if (GetObjectHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}


}

//Get World location of line trace through cross hair ,true if hits landscape
bool ATankPlayerController::GetObjectHitLocation(FVector &HitLocation) const 
{
	//Find the cross hair position
	int32 ViewportSizeX, ViewPortSizeY;
	FVector CameraWorldLocation, LookDirection;

	GetViewportSize(ViewportSizeX, ViewPortSizeY);

	//Returns the position of Crossover in 2D vector
	auto ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewPortSizeY*CrossHairYLocation);

	//Projects Screen Location to World space
	//Returns true on successful projection
	if (GetLookingDirection(ScreenLocation, LookDirection)&&
		GetHitObjectLocation(LookDirection, HitLocation)) //Get HitLocation if successfully hit a visual object
	{
		//LineTrace to that object and return its hitLocation
			return true;
	}
		
	return false;
}

//Projects Screen Location 2d to World Space
bool ATankPlayerController::GetLookingDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection);
}

//LIne trace and return the location of Hit object
bool ATankPlayerController::GetHitObjectLocation(FVector &LookDirection,FVector &HitLocation ) const
{
	FHitResult HitResult;
	FVector  Start = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = Start + (LookDirection*LineTraceRange);

	//LineTrace and Get REsult in HitResult
	if (GetWorld()->LineTraceSingleByChannel
	(
		HitResult,
		Start,
		EndLocation,
		ECollisionChannel::ECC_Visibility             //Basically Hit any target that is visible
	))
		//update HitLocation
	{
		HitLocation = HitResult.Location;
			return true;
	}
	HitLocation = FVector(0);
	return false;

}