// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BombermanGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BOMBERMAN_API UBombermanGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	const int32 MAX_LIVES = 100;

	UBombermanGameInstance();

	UFUNCTION(BlueprintCallable, Category = "Lives")
	int32 AddLives(int32 NumLives);
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Setup")
	int32 Lives;

	UFUNCTION(BlueprintCallable,Category = "Spawning")
	void TakeLife();

	UFUNCTION(BlueprintCallable,BlueprintPure,Category = "Getters")
	int32 GetLives() const { return Lives; }
};
