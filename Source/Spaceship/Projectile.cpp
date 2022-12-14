// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}
	if (!CollisionComp)
	{
		CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
		RootComponent = CollisionComp;
	}

	if (!ProjectileMovementComponent)
	{
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

		// SetUpdatedComponent selects the component to be moved by the movement component
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComp);

		ProjectileMovementComponent->InitialSpeed = 3000.f;
		ProjectileMovementComponent->MaxSpeed = 3000.f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = false;
		ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	}

	
	MissileTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MissileTrailEffect"));
	MissileTrail->SetupAttachment(RootComponent);
	

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}


