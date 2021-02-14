// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtractionActor.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"


// Sets default values
AFPSExtractionActor::AFPSExtractionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.0f));

	RootComponent = OverlapComp;

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->DecalSize = OverlapComp->GetUnscaledBoxExtent();
	DecalComp->SetupAttachment(OverlapComp);

}

// Called when the game starts or when spawned
void AFPSExtractionActor::BeginPlay()
{
	Super::BeginPlay();
	
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionActor::HandleOverlap);
	OverlapComp->SetHiddenInGame(false);
}

void AFPSExtractionActor::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	AFPSCharacter* MyPawn = Cast<AFPSCharacter>(OtherActor);
	if (MyPawn) {

		UE_LOG(LogTemp, Log, TEXT("Overlapped with extraction zone"));

		if (MyPawn->bIsCarryingObjective) {

			AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
			if (GM) {
				GM->CompleteMission(MyPawn, true);
			}
		}
		else {
			UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
		}
	}
}

