// Fill out your copyright notice in the Description page of Project Settings.

#include "June13.h"
#include "LobbyGameState.h"
#include "Net/UnrealNetwork.h"

//Required for UPROPERTY replication
void ALobbyGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyGameState, CurrentSelectedMap);
	DOREPLIFETIME(ALobbyGameState, SpectatorTeamID);

}

void ALobbyGameState::Server_SetCurrentSelectedMap(FMapInfo MapInfo)
{
	UE_LOG(YourLog, Warning, TEXT("ALobbyGameState::ServerSetCurrentSelectedMap")); 
	//Make sure server running only
	if (HasAuthority())
	{
		UE_LOG(YourLog, Warning, TEXT("ALobbyGameState::ServerSetCurrentSelectedMap isAuthority"));

		CurrentSelectedMap = MapInfo;

		//Kick all players states into spectator mode
		for (auto& PlayerState : PlayerArray)
		{
			ALobbyPlayerState *LobbyPlayerState = Cast<ALobbyPlayerState>(PlayerState);
			if (LobbyPlayerState)
			{
				LobbyPlayerState->SetTeamID(SpectatorTeamID);
			}
		}

		/*
			Update Team Info
		 */
		//Remove old team infos
		for (auto& OldTeamInfo : TeamInfos)
		{
			for (auto& PlayerState : OldTeamInfo.PlayerStates)
			{
				OldTeamInfo.PlayerStates.Remove(PlayerState);
			}
		}
			
		//Create new team infos
		TArray<FTeamInfo> NewTeamInfos; 
		for (int i=0; i<MapInfo.TeamCount; i++)
		{
			FTeamInfo NewTeamInfo;
			NewTeamInfo.TeamSize = MapInfo.TeamSize;
			NewTeamInfo.TeamID = i;
			NewTeamInfos.Add(NewTeamInfo);
		}

		//Replace
		TeamInfos = NewTeamInfos;

	}


}

FMapInfo ALobbyGameState::GetCurrentSelectedMap()
{
	return CurrentSelectedMap;	
}

void ALobbyGameState::Server_ChangePlayerStateTeamID(ALobbyPlayerState *PlayerState, int32 TeamID)
{
	UE_LOG(YourLog, Warning, TEXT("ALobbyGameState::Server_ChangePlayerStateTeamID"));

	if (HasAuthority())
	{
		UE_LOG(YourLog, Warning, TEXT("ALobbyGameState::Server_ChangePlayerStateTeamID has Authority"));

		if (TeamInfos.IsValidIndex(TeamID) || TeamID == SpectatorTeamID)
		{
			UE_LOG(YourLog, Warning, TEXT("ALobbyGameState::Server_ChangePlayerStateTeamID teamID is valid"));

			//Remove Self from previous team id if its not spectator
			int32 currentTeamID = PlayerState->GetTeamID();
			if (currentTeamID != SpectatorTeamID)
			{
				if (TeamInfos.IsValidIndex(currentTeamID))
				{
					TeamInfos[currentTeamID].PlayerStates.Remove(PlayerState);
				}
			}

			//Set New Team ID on PlayerState
			PlayerState->SetTeamID(TeamID);

			if (TeamID != SpectatorTeamID)
			{
				UE_LOG(YourLog, Warning, TEXT("ALobbyGameState::Server_ChangePlayerStateTeamID Adding to Team :%i"),TeamID);
				//Add PlayerState to new Team
				TeamInfos[TeamID].PlayerStates.Add(PlayerState);
			}
		}


	}
}