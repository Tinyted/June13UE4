// Fill out your copyright notice in the Description page of Project Settings.

#include "June13.h"
#include "LobbyPlayerState.h"
#include "Net/UnrealNetwork.h"


int32 ALobbyPlayerState::GetTeamID()
{
	return mTeamID;
}

void ALobbyPlayerState::SetTeamID(int32 TeamID)
{
	mTeamID = TeamID;
}

bool ALobbyPlayerState::GetReadyStatus()
{
	return mReady;
}

void ALobbyPlayerState::ReadyPlayer(bool ready)
{
	mReady = ready;
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


