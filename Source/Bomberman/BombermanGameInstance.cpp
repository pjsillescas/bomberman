// Fill out your copyright notice in the Description page of Project Settings.

#include "BombermanGameInstance.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UBombermanGameInstance::UBombermanGameInstance()
{
	Lives = 3;
}

void UBombermanGameInstance::TakeLife()
{
	Lives--;

	if (Lives <= 0)
	{
		//RestartPlayerAtPlayerStart(getplayerpa);
	}
	else
	{
		//		FString Command = "restartLevel";
		//		GetWorld()->Exec(GetWorld(),*Command);
		//ResetLevel();
		FString ThisLevel = GetWorld()->GetMapName();
		UE_LOG(LogTemp, Warning, TEXT("Restarting level '%s'"), *ThisLevel);
		//UGameplayStatics::OpenLevel(GetWorld(), *ThisLevel);
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap"), TRAVEL_Absolute);
	}
}

int32 UBombermanGameInstance::AddLives(int32 NumLives)
{
	UE_LOG(LogTemp,Warning,TEXT("Adding %i lives..."),NumLives);

	Lives = FMath::Clamp<int32>(Lives + NumLives, 0, MAX_LIVES);

	return Lives;
}
