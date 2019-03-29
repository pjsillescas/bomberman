// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BombermanGameMode.generated.h"

UCLASS(minimalapi)
class ABombermanGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	int32 Lives;

public:
	ABombermanGameMode();

	UFUNCTION(BlueprintCallable,BlueprintPure,Category = "Setup")
	int32 GetLives() const { return Lives; }

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void TakeLife();
};



