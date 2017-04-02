// Tank Nation Game Develped By Freedom911.For Copyright ask the user MsFreedom911@gmail.com

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKNATION_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();


	UFUNCTION(BlueprintImplementableEvent, Category = "Camera", meta = (DisplayName = "Camera Shake ~ Add Camera Shake on Take Damage event"))
	void CameraShakeEvent(float scale);


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void LaunchProjectile(float Speed,AActor*SetActorToIgnore);

private:

	//Actor to ignore whileCollision
	AActor*ActorToIgnore;

	UProjectileMovementComponent *ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UStaticMeshComponent * CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UParticleSystemComponent * LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UParticleSystemComponent * ImpactBlast = nullptr;

	//This is impulse Force x change in time see wikipedia
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	URadialForceComponent *ExplosionForce = nullptr;

	//This is impulse Force x change in time see wikipedia
	UPROPERTY(EditAnywhere, Category = "Setup")
    float DestroyDelay = 2.f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float ProjectileDamage = 10.f;


	void ProjectileDestroyerTimer();

	UFUNCTION()
	void OnHit(UPrimitiveComponent*HitComponent, AActor* OtherActor,
			   UPrimitiveComponent*OtherComponent, FVector NormalImpulse,
		       const FHitResult&Hit);

	
};
