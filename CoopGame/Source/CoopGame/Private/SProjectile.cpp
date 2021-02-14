// Fill out your copyright notice in the Description page of Project Settings.


#include "SProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ASProjectile::ASProjectile()
{
 	ProjectileComp = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileComp"));
    ProjectileComp->InitSphereRadius(5.0f);
    ProjectileComp->SetCollisionProfileName("Projectile");

    RootComponent = ProjectileComp;

	ExplosionComp = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionComp"));
	ExplosionComp->InitSphereRadius(20.0f);
    ExplosionComp->SetVisibleFlag(false);

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->UpdatedComponent = ProjectileComp;
    ProjectileMovement->InitialSpeed = 3000.0f;
    ProjectileMovement->MaxSpeed = 3000.0f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = true;

    InitialLifeSpan = 2.0f;
}

void ASProjectile::Detonate()
{
    ExplosionComp->SetVisibleFlag(true);
}
