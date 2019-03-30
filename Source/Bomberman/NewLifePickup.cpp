// Fill out your copyright notice in the Description page of Project Settings.

#include "NewLifePickup.h"
#include "BombermanCharacter.h"
#include "BombermanGameInstance.h"

void ANewLifePickup::DoPickupEffect_Implementation(AActor* Actor)
{
	Cast<UBombermanGameInstance>(GetGameInstance())->AddLives(1);
}
