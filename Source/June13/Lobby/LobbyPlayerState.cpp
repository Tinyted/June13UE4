// Fill out your copyright notice in the Description page of Project Settings.

#include "June13.h"
#include "LobbyPlayerState.h"

int8 ALobbyPlayerState::GetTeamID()
{
	return mTeamID;
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


