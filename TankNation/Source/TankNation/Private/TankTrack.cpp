// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#include "TankNation.h"
#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;	
}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}


void UTankTrack::OnHit(UPrimitiveComponent*HitComponent, AActor* OtherActor,
	UPrimitiveComponent*OtherComponent, FVector NormalImpulse,
	const FHitResult&Hit)
{
   auto Time = GetWorld()->GetTimeSeconds();
	DriveTrack();
//	ApplySideWaysForce();
	CurrentThrottle = 0.f;
}

void UTankTrack::ApplySideWaysForce()
{
	//Calculate Slippage Speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//- Slippage because we want to correct it .So we want correction speed in
	//oppositie of tank right vector
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	//Calculate Force that needs to be applied to avoid slipping
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //Since 2 tank tracks
	TankRoot->AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float Value)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Value, -1, 1);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector()*CurrentThrottle*MaxForcePerTrack;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


