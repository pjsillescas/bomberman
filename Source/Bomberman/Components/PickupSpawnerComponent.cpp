// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupSpawnerComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"

// Sets default values for this component's properties
UPickupSpawnerComponent::UPickupSpawnerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	PickupSpawnProbability = 0;
	
	// ...
}


// Called when the game starts
void UPickupSpawnerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

float UPickupSpawnerComponent::GetTotalProbability()
{
	float TotalProbability = 0;

	for (auto Config : PickupSpawnConfig)
	{
		TotalProbability += Config.Probability;
	}

	return TotalProbability;
}

void UPickupSpawnerComponent::TrySpawn()
{
	float RandomNumber = FMath::FRandRange(0, 1);

	if (RandomNumber <= PickupSpawnProbability && PickupSpawnConfig.Num() > 0)
	{
		float TotalProbability = GetTotalProbability();

		float PickupProbability = FMath::FRandRange(0, TotalProbability);

		int32 ChosenPickupToSpawn = 0;
		float SubTotal = 0;
		while (ChosenPickupToSpawn < PickupSpawnConfig.Num() && SubTotal < PickupProbability)
		{
			SubTotal += PickupSpawnConfig[ChosenPickupToSpawn].Probability;
			ChosenPickupToSpawn++;
		}

		if (ChosenPickupToSpawn >= PickupSpawnConfig.Num())
			ChosenPickupToSpawn = PickupSpawnConfig.Num() - 1;

		GetWorld()->SpawnActor<AActor>(PickupSpawnConfig[ChosenPickupToSpawn].PickupClass, GetOwner()->GetActorTransform(), FActorSpawnParameters());
	}
}


// Called every frame
void UPickupSpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

