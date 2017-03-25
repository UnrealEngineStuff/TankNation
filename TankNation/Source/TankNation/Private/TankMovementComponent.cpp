// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#include "TankNation.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	LeftTrack = LeftTrackToSet ;
    RightTrack = RightTrackToSet;

}
//for AI tanks
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//No Need to call super as we are replacing  code
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	
	auto MoveVector = FVector::DotProduct(TankForward,AIForwardIntention);
	IntendMoveForward(MoveVector);

	auto RotateVector = FVector::CrossProduct(TankForward,AIForwardIntention).Z;
	IntendMoveRight(RotateVector);
}

void UTankMovementComponent::IntendMoveForward(float Value)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Value);
	RightTrack->SetThrottle(Value);

}

void UTankMovementComponent::IntendMoveRight(float Value)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Value);
	RightTrack->SetThrottle(-Value);
}

