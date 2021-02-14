// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBlackholeActor.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API AFPSBlackholeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSBlackholeActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Controls the visible mesh for the actor
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp;

	// Controls the collision radius for the actor
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* InnerSphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* OuterSphereComp;

	UFUNCTION()
		void OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	

};
