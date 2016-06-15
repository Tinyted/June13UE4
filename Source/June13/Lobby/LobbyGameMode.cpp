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
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Constructor for ALobbyGameMode"));
	}

	GameStateClass = ALobbyGameState::StaticClass();
	PlayerControllerClass = ALobbyPlayerController::StaticClass();
	PlayerStateClass = ALobbyPlayerState::StaticClass();

}

void ALobbyGameMode::InitGameState() 
{
	Super::InitGameState();
	//SetupMapInfo();
	ALobbyGameState *LobbyGameState = Cast<ALobbyGameState>(GameState);
	if (LobbyGameState)
	{
		UE_LOG(YourLog, Warning, TEXT("LobbyGameMode requesting LobbyGameState to setDefaultMap()")); //Window->Output Log to show log
		LobbyGameState->setDefaultSelectedMap();
		LobbyGameState->SpectatorTeamID = -1;
	}
	
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

	TestMap.GameModeInfo = TestGameMode;

	ALobbyGameState *LobbyGameState = Cast<ALobbyGameState>(GameState);
	LobbyGameState->MapsAvailable.Add(TestMap);
}


void ALobbyGameMode::PostLogin(APlayerController* NewPlayer) 
{
	UE_LOG(YourLog, Warning, TEXT("ALobbyGameMode::Post Login for NewPlayer %s"),*NewPlayer->PlayerState->PlayerName); //Window->Output Log to show log

	ALobbyPlayerState *LobbyPlayerState = Cast<ALobbyPlayerState>(NewPlayer->PlayerState);
	if (LobbyPlayerState)
	{
		int32 spectator_teamid = -1;
		ALobbyGameState *LobbyGameState = Cast<ALobbyGameState>(GameState);
		if (LobbyGameState)
		{
			spectator_teamid = LobbyGameState->SpectatorTeamID;
		}
		LobbyPlayerState->SetTeamID(spectator_teamid);
	}

	InformServerLocalPlayerControllersOfChanges();

	//Do the stuff above then work on the Super::PostLogin which involves calling the blueprint Event
	Super::PostLogin(NewPlayer);

}

bool ALobbyGameMode::ServerStartGame()
{
	UE_LOG(YourLog, Warning, TEXT("ALobbyGameMode::ServerStartGame"));

	//Check all player states to see if everyone is readied
	TArray<APlayerState*> PlayerStates = GameState->PlayerArray;

	bool allReady = true;
		
	for (auto& PlayerState : PlayerStates)
	{
		ALobbyPlayerState *LobbyPlayerState = Cast<ALobbyPlayerState>(PlayerState);
		if (LobbyPlayerState && LobbyPlayerState->GetReadyStatus() == false)
		{
			allReady = false;
			break;
		}
	}

	if (allReady)
	{
		//Start CountDown for ServerTravel()
		TravelTimerCountDown = 0;
		GetWorld()->GetTimerManager().SetTimer(ServerTravelTimer, this, &ALobbyGameMode::ServerTravelCountDown, 1.0f, true);
		
	}

	return allReady;
}

void ALobbyGameMode::ServerTravelCountDown()
{
	TravelTimerCountDown++;
	UE_LOG(YourLog, Warning, TEXT("ALobbyGameMode::ServerTravelCountDown :%i"),TravelTimerCountDown);

	if (TravelTimerCountDown == 5)
	{
		GetWorld()->GetTimerManager().ClearTimer(ServerTravelTimer);
		ServerTravel();
	}
}

void ALobbyGameMode::ServerTravel() 
{
	bUseSeamlessTravel = true;
	UE_LOG(YourLog, Warning, TEXT("ALobbyGameMode::ServerTravel")); //Window->Output Log to show log

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("ALobbyGameMode::ServerTravel ONSCREENMSG"));
	}

	//TODO get selected Map and GameMode from GameState, and travel to that instead
	ALobbyGameState *LobbyGameState = Cast<ALobbyGameState>(GameState);
	FMapInfo MapInfo = LobbyGameState->GetCurrentSelectedMap(); //Don't need to check for server, since we are GameMode, and GameMode only exist on server
	FGameModeInfo GameMode = MapInfo.GameModeInfo;

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

void ALobbyGameMode::InformServerLocalPlayerControllersOfChanges()
{

	UE_LOG(YourLog, Warning, TEXT("ALobbyGameMode::InformOwningPlayerControllerOfChanges")); //Window->Output Log to show log

	//Find all player controllers on server and let it know data is changed
	for (auto& PlayerState : GameState->PlayerArray)
	{
		AActor *Owner = PlayerState->GetOwner(); //If the PlayerState has an owner
		if (Owner)
		{
			ALobbyPlayerController *LobbyPlayerController = Cast<ALobbyPlayerController>(Owner);
			if (LobbyPlayerController)
			{
				if (LobbyPlayerController->IsLocalController())
				{
					LobbyPlayerController->Local_DataChanged();
				}
			}
		}
	}
}
