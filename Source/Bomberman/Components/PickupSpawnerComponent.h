// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BasicPickup.h"
#include "PickupSpawnerComponent.generated.h"

USTRUCT(BlueprintType)
struct FPickupSpawnConfig
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<ABasicPickup> PickupClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Probability;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOMBERMAN_API UPickupSpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPickupSpawnerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float PickupSpawnProbability;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TArray<FPickupSpawnConfig> PickupSpawnConfig;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable,Category = "Effects")
	void TrySpawn();

private:
	float GetTotalProbability();
};
