// Fill out your copyright notice in the Description page of Project Settings.

#include "June13.h"
#include "TWGameMode.h"
#include "TWPlayerState.h"
#include "TWGameState.h"

void ATWGameMode::PostSeamlessTravel()
{
	Super::PostSeamlessTravel(); //Let the super's implementation be done first
	//Old controllers should be considered gone, and new controllers are created in its place

	//GameState should exist already, since it's created in PreInitializeComponents()
	ATWGameState *TWGameState = Cast<ATWGameState>(GameState);

	//Tell GameState to figure out what the teams are like. 
	if (TWGameState)
	{
		TWGameState->ServerSetupTeamInfo();
	}
}

void ATWGameMode::PostLogin(APlayerController *NewPlayer)
{
	//Handle code here

	Super::PostLogin(NewPlayer);
}

bool ATWGameMode::ReadyToStartMatch_Implementation()
{
	//Make sure all players are connected

	return false;
}