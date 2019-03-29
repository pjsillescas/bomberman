// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BombermanGameMode.h"
#include "BombermanCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABombermanGameMode::ABombermanGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	Lives = 3;
}


void ABombermanGameMode::TakeLife()
{
	Lives--;

	if (Lives <= 0)
	{
		//RestartPlayerAtPlayerStart(getplayerpa);
	}
	else
	{
		;
	}
}
