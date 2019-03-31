// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicPickup.h"
#include "AddBombPickup.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API AAddBombPickup : public ABasicPickup
{
	GENERATED_BODY()
	
protected:
	void DoPickupEffect_Implementation(AActor* Actor);

};
