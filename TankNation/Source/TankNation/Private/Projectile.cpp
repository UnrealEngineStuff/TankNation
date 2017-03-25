// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#include "TankNation.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	//TODO Check here Srajan
	//we need to hide
	CollisionMesh->SetVisibility(false);
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));

	LaunchBlast->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);

	//for impact
	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	//TODO update to new method
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Radial Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	ProjectileMovement->bAutoActivate = false;




}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

void AProjectile::OnHit(UPrimitiveComponent*HitComponent, AActor* OtherActor,
						UPrimitiveComponent*OtherComponent, FVector NormalImpulse,
						const FHitResult&Hit)
{

	LaunchBlast->Deactivate();
	ImpactBlast->Activate();

	
	ExplosionForce->FireImpulse();
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		ProjectileDamage,
		GetActorLocation(),
		ExplosionForce->Radius, //for consistency
		UDamageType::StaticClass(),
		TArray<AActor*>()      //Damage All Actors Check if we want it for all
	);
	FTimerHandle ParticleDestroyer;
	GetWorld()->GetTimerManager().SetTimer(ParticleDestroyer, this,
		                                  &AProjectile::ProjectileDestroyerTimer,
		                                  DestroyDelay, false);
}

//Can be made more efficent
//By maintaining total projectile count if it is greater than 
//fixed amount then delete them
void AProjectile::ProjectileDestroyerTimer()
{
	Destroy();
}

void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector*Speed);
	ProjectileMovement->Activate();

}