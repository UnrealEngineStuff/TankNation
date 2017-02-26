// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#include "TankNation.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if (LeftTrackToSet)
	{
		LeftTrack=LeftTrackToSet ;
	}

	if (RightTrackToSet)
	{
		RightTrack = RightTrackToSet;
	}

}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//No Need to call super as we are replacing  code
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto MoveVector = FVector::DotProduct(TankForward,AIForwardIntention);
	IntendMoveForward(MoveVector);
	//UE_LOG(LogTemp,Warning,TEXT("Tank Name :%s moving with velocity %s"),*GetOwner()->GetName(),*MoveVelocity.GetSafeNormal().ToCompactString())
}

void UTankMovementComponent::IntendMoveForward(float Value)
{

	if (!LeftTrack || !RightTrack)
		return;

	LeftTrack->SetThrottle(Value);
	RightTrack->SetThrottle(Value);

}

void UTankMovementComponent::IntendMoveRight(float Value)
{
	if (!LeftTrack || !RightTrack)
		return;

	LeftTrack->SetThrottle(Value);
	RightTrack->SetThrottle(-Value);

}

