// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bomb.h"
#include "ArcadeBomb.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API AArcadeBomb : public ABomb
{
	GENERATED_BODY()
	
public:
	AArcadeBomb();

	const float TILE_LENGTH = 90;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Setup")
	int32 ScopeTiles;

protected:
	virtual void Explode();
};
