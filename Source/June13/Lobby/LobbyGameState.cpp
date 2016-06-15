// Fill out your copyright notice in the Description page of Project Settings.

#include "June13.h"
#include "LobbyGameState.h"
#include "LobbyPlayerController.h"
#include "Net/UnrealNetwork.h"

//Required for UPROPERTY replication
void ALobbyGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyGameState, mCurrentSelectedMap);
	DOREPLIFETIME(ALobbyGameState, SpectatorTeamID);
	DOREPLIFETIME(ALobbyGameState, mTeamInfos);

}

void ALobbyGameState::Server_SetCurrentSelectedMap(FMapInfo MapInfo)
{
	UE_LOG(YourLog, Warning, TEXT("ALobbyGameState::ServerSetCurrentSelectedMap")); 
	//Make sure server running only
	if (HasAuthority())
	{
		UE_LOG(YourLog, Warning, TEXT("ALobbyGameState::ServerSetCurrentSelectedMap isAuthority"));

		mCurrentSelectedMap = MapInfo;

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
		for (auto& OldTeamInfo : mTeamInfos)
		{
			for (auto& PlayerState : OldTeamInfo.PlayerStates) //Avoid any possible leaks?
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
		mTeamInfos = NewTeamInfos;

	}
}

FMapInfo ALobbyGameState::GetCurrentSelectedMap()
{
	return mCurrentSelectedMap;	
}

void ALobbyGameState::SetDefaultSelectedMap_Implementation()
{
	if (MapsAvailable.Num() == 0)
	{
		return;
	}
	else 
	{
		mCurrentSelectedMap = MapsAvailable[0];
	}
}

TArray<FTeamInfo> ALobbyGameState::GetTeamInfo()
{
	return mTeamInfos;
}

void ALobbyGameState::AddPlayerStateToTeam(ALobbyPlayerState *PlayerState, int32 TeamID)
{
	if (TeamID != SpectatorTeamID && mTeamInfos.IsValidIndex(TeamID))
	{
		UE_LOG(YourLog, Warning, TEXT("ALobbyGameState::AddPlayerStateToTeam Adding to Team :%i"), TeamID);
		//Add PlayerState to new Team
		mTeamInfos[TeamID].PlayerStates.Add(PlayerState); //REPLICATED
	}
}

void ALobbyGameState::OnRep_TeamInfoChanged_Implementation()
{
	for (auto& PlayerState : PlayerArray)
	{
		AActor *Owner = PlayerState->GetOwner();
		ALobbyPlayerController *PlayerController = Cast<ALobbyPlayerController>(Owner);
		if (PlayerController)
		{
			PlayerController->Local_DataChanged();
		}
	}
}

void ALobbyGameState::RemovePlayerStateFromTeam(ALobbyPlayerState *PlayerState)
{
	int32 currentTeamID = PlayerState->GetTeamID();
	if (currentTeamID != SpectatorTeamID)
	{
		if (mTeamInfos.IsValidIndex(currentTeamID))
		{
			mTeamInfos[currentTeamID].PlayerStates.Remove(PlayerState); //REPLICATED
		}
	}
}

void ALobbyGameState::AddPlayerState(APlayerState *PlayerState)
{
	Super::AddPlayerState(PlayerState);
	InformLocalPlayerControllerDataChanged();
}

void ALobbyGameState::InformLocalPlayerControllerDataChanged()
{
	for (auto& PlayerState : PlayerArray)
	{
		AActor *Owner = PlayerState->GetOwner();
		if (Owner)
		{
			ALobbyPlayerController *PlayerController = Cast<ALobbyPlayerController>(Owner);
			if (PlayerController)
			{
				PlayerController->Local_DataChanged();
			}
		}
		
	}
}