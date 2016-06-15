// Fill out your copyright notice in the Description page of Project Settings.

#include "June13.h"
#include "LobbyPlayerState.h"
#include "LobbyGameState.h"
#include "Net/UnrealNetwork.h"


int32 ALobbyPlayerState::GetTeamID()
{
	return mTeamID;
}

void ALobbyPlayerState::SetTeamID_Implementation(int32 TeamID)
{
	if (HasAuthority())
	{
		mTeamID = TeamID;
	}
}

bool ALobbyPlayerState::SetTeamID_Validate(int32 TeamID)
{
	//Might want to check if team id is valid
	return true;
}


void ALobbyPlayerState::OnRep_TeamIDChanged_Implementation()
{
	AGameState *GameState = GetWorld()->GetGameState();
	ALobbyGameState *LobbyGameState = Cast<ALobbyGameState>(GameState);
	if (LobbyGameState)
	{
		LobbyGameState->OnRep_TeamInfoChanged();
	}

}

bool ALobbyPlayerState::GetReadyStatus()
{
	return mReady;
}

void ALobbyPlayerState::ReadyPlayer_Implementation(bool ready)
{
	if (HasAuthority())
	{
		mReady = ready;
	}

}

//No validation really done here, just return true always
bool ALobbyPlayerState::ReadyPlayer_Validate(bool ready)
{
	return true;
}

void ALobbyPlayerState::OnRep_ReadyChanged_Implementation()
{
	AGameState *GameState = GetWorld()->GetGameState();
	ALobbyGameState *LobbyGameState = Cast<ALobbyGameState>(GameState);
	if (LobbyGameState)
	{
		LobbyGameState->OnRep_ReadyChanged();
	}
}

//Required for UPROPERTY replication
void ALobbyPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyPlayerState, mTeamID);
	DOREPLIFETIME(ALobbyPlayerState, mReady);
}


void ALobbyPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	//Check if PlayerState conforms to IPlayerStateInterface http://stackoverflow.com/questions/22609736/check-if-a-is-a-subclass-of-b
	ILobbyPlayerStateInterface *p = Cast<ILobbyPlayerStateInterface>(PlayerState); //dynamic_cast doesnt work in UE4
	if (p)
	{
		mTeamID = p->GetTeamID();
	}
}


