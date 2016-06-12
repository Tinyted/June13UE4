// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "LobbyPlayerStateInterface.h"
#include "LobbyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class JUNE13_API ALobbyPlayerState : public APlayerState, public ILobbyPlayerStateInterface
{
	GENERATED_BODY()
	
public:

	virtual int8 GetTeamID();
	void CopyProperties(APlayerState* PlayerState) override;

protected:
	int8 mTeamID;
	
	
};
