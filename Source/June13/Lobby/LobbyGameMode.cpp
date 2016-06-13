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
	//SetupMapInfo();
}

void ALobbyGameMode::SetupMapInfo() 
{
	FMapInfo TestMap;
	TestMap.MapName = FString(TEXT("Test Map Name"));
	TestMap.TeamSize = 2;
	TestMap.TeamCount = 2;
	TestMap.MapURL = FString(TEXT("/Game/TestGame/TestMap"));

	FGameModeInfo TestGameMode;
	TestGameMode.GameModeName = FString(TEXT("Test Game Mode"));
	TestGameMode.GameModeURL = FString(TEXT("/Game/TestGame/TestGameMode.TestGameMode_C"));

	TestMap.SupportModes.Add(TestGameMode.GameModeName);


	ALobbyGameState *LobbyGameState = Cast<ALobbyGameState>(GameState);
	LobbyGameState->MapsAvailable.Add(TestMap);
	LobbyGameState->GameModesAvailable.Add(TestGameMode);
}


void ALobbyGameMode::PostLogin(APlayerController* NewPlayer) 
{
	Super::PostLogin(NewPlayer);

	UE_LOG(YourLog, Warning, TEXT("ALobbyGameMode::Post Login")); //Window->Output Log to show log

	TArray<class APlayerState*> playerArray = GameState->PlayerArray;
	for (auto& Player : playerArray) 
	{
		UE_LOG(YourLog, Warning, TEXT("Player Name : %s"), *Player->PlayerName); //Window->Output Log to show log
	}
}

void ALobbyGameMode::ServerTravel() 
{
	bUseSeamlessTravel = true;
	UE_LOG(YourLog, Warning, TEXT("ALobbyGameMode::ServerTravel")); //Window->Output Log to show log

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("ALobbyGameMode::ServerTravel"));
	}

	//TODO get selected Map and GameMode from GameState, and travel to that instead
	ALobbyGameState *LobbyGameState = Cast<ALobbyGameState>(GameState);
	FMapInfo MapInfo = LobbyGameState->CurrentSelectedMap;
	FGameModeInfo GameMode = LobbyGameState->CurrentSelectedMode;

	FString MapURL = MapInfo.MapURL;
	FString GameModeURL = GameMode.GameModeURL;

	FString URL = MapURL + FString(TEXT("?game=")) + GameModeURL + FString(TEXT("?listen"));
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, URL);
	}
	GetWorld()->ServerTravel(URL);
	//GetWorld()->ServerTravel(TEXT("/Game/TestGame/TestMap?game=/Game/TestGame/TestGameMode.TestGameMode_C?listen"));
}