// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSLaunchpadActor.h"
#include "FPSCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values.
AFPSLaunchpadActor::AFPSLaunchpadActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RootComponent = MeshComp;

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);

	OverlapComp->SetupAttachment(MeshComp);

	LaunchVector = FVector::FVector(1000.0f, 0.0f, 1000.0f);


}

// Called when the game starts or when spawned.
void AFPSLaunchpadActor::BeginPlay()
{
	Super::BeginPlay();

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchpadActor::HandleOverlap);
	
}

void AFPSLaunchpadActor::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	auto ActorName = this->GetName();

	//UE_LOG(LogTemp, Log, TEXT("%s detected overlap event"), *ActorName);
	// The overlapping actor is a character.
	AFPSCharacter* Interactor = Cast<AFPSCharacter>(OtherActor);
	if (Interactor) {
		Interactor->LaunchCharacter(LaunchVector, true, true);

		UGameplayStatics::SpawnEmitterAtLocation(this, InteractFX, GetActorLocation());
	}
	// The overlapping actor is a component that is simulating physics.
	else if (OtherComp && OtherComp->IsSimulatingPhysics()) {
		OtherComp->AddImpulse(LaunchVector, NAME_None, true);

		UE_LOG(LogTemp, Log, TEXT("OtherComp Overlap detected."));

		UGameplayStatics::SpawnEmitterAtLocation(this, InteractFX, GetActorLocation());
	}
}