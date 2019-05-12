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
	
protected:
	virtual void Explode();
};
