// Fill out your copyright notice in the Description page of Project Settings.

#include "June13.h"
#include "LobbyGameMode.h"
#include "LobbyGameState.h"
#include "LobbyPlayerController.h"
#include "LobbyPlayerState.h"

ALobbyGameMode::ALobbyGameMode(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UE_LOG(YourLog, Warning, TEXT("Constructor for ALobbyGameMode")); //Window->Output Log to show log

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Constructor for ALobbyGameMode"));
	}

	GameStateClass = ALobbyGameState::StaticClass();
	PlayerControllerClass = ALobbyPlayerController::StaticClass();
	PlayerStateClass = ALobbyPlayerState::StaticClass();

}

void ALobbyGameMode::InitGameState() 
{
	Super::InitGameState();
	SetupMapInfo();
}

void ALobbyGameMode::SetupMapInfo() 
{
	FMapInfo testMap;
	testMap.MapName = FString(TEXT("Test Map Name"));
	testMap.TeamSize = 2;
	testMap.TeamCount = 2;

	ALobbyGameState *LobbyGameState = Cast<ALobbyGameState>(GameState);
	LobbyGameState->MapsAvailable.Add(testMap);
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer) 
{
	Super::PostLogin(NewPlayer);

	UE_LOG(YourLog, Warning, TEXT("Post Login")); //Window->Output Log to show log

	TArray<class APlayerState*> playerArray = GameState->PlayerArray;
	for (auto& Player : playerArray) 
	{
		UE_LOG(YourLog, Warning, TEXT("Player Name : %s"), *Player->PlayerName); //Window->Output Log to show log
	}
}