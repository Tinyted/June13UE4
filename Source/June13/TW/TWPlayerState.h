// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "../Lobby/LobbyPlayerStateInterface.h"
#include "TWPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class JUNE13_API ATWPlayerState : public APlayerState, public ILobbyPlayerStateInterface
{
	GENERATED_BODY()
	
public: 
	int32 GetTeamID();
	void SetTeamID(int32 TeamID);
	
protected:

	int32 mTeamID;

};
