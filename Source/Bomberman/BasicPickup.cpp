// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicPickup.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "BombermanGameInstance.h"

// Sets default values
ABasicPickup::ABasicPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));

	Mesh->OnComponentBeginOverlap.AddDynamic(this,&ABasicPickup::OnPickupBeginOverlap);
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->SetCollisionProfileName(FName("OverlapAll"));
}

// Called when the game starts or when spawned
void ABasicPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABasicPickup::IsPlayer(AActor* Actor) const
{
	APawn* Pawn = Cast<APawn>(Actor);
	return (Pawn != nullptr) && Pawn->GetController()->IsPlayerController();
}

void ABasicPickup::OnPickupBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning,TEXT("Overlapping"));

	if (IsPlayer(OtherActor))
	{
		Cast<UBombermanGameInstance>(GetGameInstance())->AddLives(1);

		Destroy();
	}
}
