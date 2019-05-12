// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicPickup.h"
#include "AddScopePickup.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API AAddScopePickup : public ABasicPickup
{
	GENERATED_BODY()
	
	virtual void DoPickupEffect_Implementation(AActor* Actor) override;

};
