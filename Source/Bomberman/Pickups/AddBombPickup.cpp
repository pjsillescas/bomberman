// Fill out your copyright notice in the Description page of Project Settings.

#include "AddBombPickup.h"
#include "BombermanCharacter.h"

void AAddBombPickup::DoPickupEffect_Implementation(AActor* Actor)
{
	ABombermanCharacter* Bomberman = Cast<ABombermanCharacter>(Actor);
	Bomberman->IncreaseMaxBombs();
}
