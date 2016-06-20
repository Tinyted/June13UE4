// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "TWGameMode.generated.h"

/*
	TWGameMode is to be the base class for any custom game modes used for actual gameplay.

	--
	In terms of data persistence from the Lobby related classes
	--
	It is to be paired with TWGameState, which conforms to the LobbyPlayerStateInterface, allowing TWGameMode to obtain the data regarding teams after a SeamlessTravel from the lobby.
	-See PostSeamlessTravel()
	Afterwards it is up to the TWGameMode to construct the proper data for its TWGameState	

	--
	In terms of MatchState
	--
	TWGameMode should also have implementation for HandleMatchIsWaitingToStart(), ReadyToStartMatch(), HandleMatchHasStarted()
	Note: once the MatchState has been changed, it will call OnMatchStateSet(), which calls the corresponding HandleMatch_____ method.

	Default implementation from AGameMode for HandleMatchIsWaitingToStart() checks for ReadyToStartMatch() which returns a bool, which then it calls BeginPlay on actors
	Default implementation from AGameMode for ReadyToStartMatch() is a blueprint native event, thus _Implementation is required, and starts when there is (NumPlayers + NumBots > 0)
	Default implementation from AGameMode for HandleMatchHasStarted() is to restart the player controllers if they have no pawn. 

	When the conditions are met to start the game, the relevant code should call StartPlay(), which checks for MatchState to be WaitingToStart and true for ReadyToStartMatch()
 
 */

UCLASS()
class JUNE13_API ATWGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	void StartPlay() override;

	/* Data peristence from Lobby related */
	//Handle Post SeamlessTravel
	void PostSeamlessTravel() override;
	
	/* Match State related*/
	//Check if match is ready to start
	UFUNCTION(BlueprintNativeEvent, Category = "Game")
	bool ReadyToStartMatch();

	//
	void PostLogin(APlayerController* NewPlayer) override;
	
	void HandleSeamlessTravelPlayer(AController*& C) override;

private:

	bool TeamSetupDone;
};
