// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UDamageType;
class UParticleSystem;

UCLASS()
class COOPGAME_API ASProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASProjectile();

	USphereComponent* GetSphereComp() const { return ProjectileComp; }

	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
		USphereComponent* ProjectileComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Explosion")
		USphereComponent* ExplosionComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Explosion")
		TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Explosion")
		UParticleSystem* ExplosionEffect;

	UFUNCTION(BlueprintCallable, Category = "Projectile")
		void Detonate();




};
