// Fill out your copyright notice in the Description page of Project Settings.


#include "AddScopePickup.h"

#include "BombermanCharacter.h"
#include "BombermanGameInstance.h"

void AAddScopePickup::DoPickupEffect_Implementation(AActor* Actor)
{
	Cast<ABombermanCharacter>(Actor)->AddScope();
}
