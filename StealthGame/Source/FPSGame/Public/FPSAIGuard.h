// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIState : uint8 {
	Idle,
	Suspicious,
	Alerted
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int PatrolPosition;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPawnSensingComponent* PawnSensingComp;

	/* Whether the guard is patrolling or not */
	UPROPERTY(EditInstanceOnly, Category = "AI")
		bool bPatrolling;

	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrolling"))
		TArray<AActor*> PatrolPoints;

	UPROPERTY(ReplicatedUsing=OnRep_GuardState)
		EAIState GuardState;

	AActor* CurrentPatrolPoint;

	FTimerHandle TimerHandle_ResetOrientation;

	FRotator OriginalRotation;

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
		void OnStateChanged(EAIState NewState);

	UFUNCTION()
		void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
		void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	UFUNCTION()
		void ResetOrientation();

	UFUNCTION()
		void OnRep_GuardState();

	void SetGuardState(EAIState NewState);

	void MoveToNextPatrolPoint();

};