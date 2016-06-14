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


