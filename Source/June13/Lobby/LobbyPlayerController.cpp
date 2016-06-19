// Fill out your copyright notice in the Description page of Project Settings.

#include "June13.h"
#include "LobbyPlayerController.h"
#include "LobbyPlayerState.h"
#include "LobbyGameMode.h"
#include "LobbyGameState.h"

void ALobbyPlayerController::BeginPlayingState()
{
	UE_LOG(YourLog, Warning, TEXT("LobbyPlayerController::BeginPlayingState")); //Window->Output Log to show log

	if (PlayerState) 
	{
		UE_LOG(YourLog, Warning, TEXT("LobbyPlayerController, PlayerState exists")); //Window->Output Log to show log
	}

	OnBeginPlayingState();
}

void ALobbyPlayerController::Server_ReadyPlayer_Implementation()
{
	//Double check it has authority
	if (HasAuthority())
	{
		//Get PlayerState
		ALobbyPlayerState *LobbyPlayerState = Cast<ALobbyPlayerState>(PlayerState);
		if (LobbyPlayerState)
		{
			bool readyStatus = LobbyPlayerState->GetReadyStatus();
			LobbyPlayerState->ReadyPlayer(!readyStatus);
			ServerPlayerController_DataChanged();
		}
	}
}

//Nothing really to validate for a ready process
bool ALobbyPlayerController::Server_ReadyPlayer_Validate()
{
	return true;
}

void ALobbyPlayerController::Server_ChangeTeam_Implementation(int32 TeamID)
{
	//Double check it has authority
	if (HasAuthority())
	{
		ALobbyPlayerState *LobbyPlayerState = Cast<ALobbyPlayerState>(PlayerState);

		AGameState *GameState = GetWorld()->GetGameState();
		ALobbyGameState *LobbyGameState = Cast<ALobbyGameState>(GameState);
		if (LobbyPlayerState && LobbyGameState)
		{
			if (LobbyPlayerState->GetTeamID() == TeamID)
			{
				UE_LOG(YourLog, Warning, TEXT("ALobbyPlayerController::Server_ChangeTeam same team id, no point changing"));

				//Same team ID, no point in changing
				return;
			}
			
			TArray<FTeamInfo> TeamInfos = LobbyGameState->GetTeamInfo();

			if (TeamInfos.IsValidIndex(TeamID) || TeamID == LobbyGameState->SpectatorTeamID)
			{
				UE_LOG(YourLog, Warning, TEXT("ALobbyPlayerController::Server_ChangeTeam teamID is valid"));

				//Remove Self from previous team id
				LobbyGameState->ServerRemovePlayerStateFromTeam(LobbyPlayerState);

				//Set New Team ID on PlayerState
				LobbyPlayerState->SetTeamID(TeamID); //REPLICATED

				LobbyGameState->ServerAddPlayerStateToTeam(LobbyPlayerState, TeamID); //REPLICATED

				LobbyPlayerState->ReadyPlayer(false); //Will be replicated

				ServerPlayerController_DataChanged();
			}
			
		}

		
	}
}

bool ALobbyPlayerController::Server_ChangeTeam_Validate(int32 TeamID)
{
	return true;
}

void ALobbyPlayerController::Server_StartGame()
{
	UE_LOG(YourLog, Warning, TEXT("ALobbyPlayerController::Server_StartGame")); //Window->Output Log to show log

	if (HasAuthority())
	{
		UE_LOG(YourLog, Warning, TEXT("ALobbyPlayerController::Server_StartGame hasAuthority")); //Window->Output Log to show log
		AGameMode* GameMode = GetWorld()->GetAuthGameMode();
		ALobbyGameMode *LobbyGameMode = Cast<ALobbyGameMode>(GameMode);
		if (LobbyGameMode)
		{
			Server_ReadyPlayer_Implementation();
			LobbyGameMode->ServerStartGame();
		}
	}
}

void ALobbyPlayerController::MultiCast_DataChanged_Implementation()
{
	UE_LOG(YourLog, Warning, TEXT("ALobbyPlayerController::MultiCast_DataChanged_Implementation")); //Window->Output Log to show log
	if (HasAuthority())
	{
		UE_LOG(YourLog, Warning, TEXT("ALobbyPlayerController::MultiCast_DataChanged_Implementation has Authority")); //Window->Output Log to show log

	}
	else 
	{
		UE_LOG(YourLog, Warning, TEXT("ALobbyPlayerController::MultiCast_DataChanged_Implementation doesnt have authority")); //Window->Output Log to show log

	}

	Local_DataChanged();
}

void ALobbyPlayerController::ServerPlayerController_DataChanged()
{
	AGameMode* GameMode = GetWorld()->GetAuthGameMode();
	ALobbyGameMode *LobbyGameMode = Cast<ALobbyGameMode>(GameMode);
	if (LobbyGameMode)
	{
		LobbyGameMode->InformServerLocalPlayerControllersOfChanges();
	}
}