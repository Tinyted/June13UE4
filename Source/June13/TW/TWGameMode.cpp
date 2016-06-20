// Fill out your copyright notice in the Description page of Project Settings.

#include "June13.h"
#include "TWGameMode.h"
#include "TWPlayerState.h"
#include "TWGameState.h"

void ATWGameMode::StartPlay()
{
	UE_LOG(YourLog, Warning, TEXT("ATWGameMode::StartPlay")); //Window->Output Log to show log
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("ATWGameMode::StartPlay"));
	}	Super::StartPlay(); //Use AGameMode's implementation
}


void ATWGameMode::PostSeamlessTravel()
{
	UE_LOG(YourLog, Warning, TEXT("ATWGameMode::PostSeamlessTravel")); //Window->Output Log to show log
	Super::PostSeamlessTravel(); //Let the super's implementation be done first
	UE_LOG(YourLog, Warning, TEXT("ATWGameMode::PostSeamlessTravel super done")); //Window->Output Log to show log
	//Old controllers should be considered gone, and new controllers are created in its place

	//GameState should exist already, since it's created in PreInitializeComponents()
	ATWGameState *TWGameState = Cast<ATWGameState>(GameState);


	//Tell GameState to figure out what the teams are like. 
	if (TWGameState)
	{
		TeamSetupDone = false;
		TWGameState->ServerSetupTeam();
		TeamSetupDone = TWGameState->ServerSetupTeamInfo();
	}
}

void ATWGameMode::PostLogin(APlayerController *NewPlayer)
{
	//Handle code here

	Super::PostLogin(NewPlayer);
}


void ATWGameMode::HandleSeamlessTravelPlayer(AController*& C)
{
	Super::HandleSeamlessTravelPlayer(C);

	UE_LOG(YourLog, Warning, TEXT("ATWGameMode::HandleSeamlessTravelPlayer")); //Window->Output Log to show log

	APlayerState *PlayerState = C->PlayerState;
	ATWPlayerState *TWPlayerState = Cast<ATWPlayerState>(PlayerState);
	if (TWPlayerState)
	{
		TWPlayerState->ClientReady = true;
	}
}


bool ATWGameMode::ReadyToStartMatch_Implementation()
{
	UE_LOG(YourLog, Warning, TEXT("ATWGameMode::ReadyToStartMatch_Implementation")); //Window->Output Log to show log
	if (!GameState)
	{
		UE_LOG(YourLog, Warning, TEXT("ATWGameMode::ReadyToStartMatch_Implementation no game state")); //Window->Output Log to show log
	}

	ATWGameState *TWGameState = Cast<ATWGameState>(GameState);
	if (!TWGameState)
	{
		UE_LOG(YourLog, Warning, TEXT("ATWGameMode::ReadyToStartMatch_Implementation TWGameState cast failed")); //Window->Output Log to show log
		return false;
	}

	//Make sure all players are connected
	for (auto& PlayerState : TWGameState->PlayerArray)
	{
		UE_LOG(YourLog, Warning, TEXT("ATWGameMode::ReadyToStartMatch_Implementation playerstate name %s"),*PlayerState->PlayerName); //Window->Output Log to show log
		ATWPlayerState *TWPlayerState = Cast<ATWPlayerState>(PlayerState);
		if (TWPlayerState)
		{
			if (!TWPlayerState->ClientReady)
			{
				UE_LOG(YourLog, Warning, TEXT("ATWGameMode::ReadyToStartMatch_Implementation client is not ready")); //Window->Output Log to show log
				return false;
			}
		}
		else 
		{
			UE_LOG(YourLog, Warning, TEXT("ATWGameMode::ReadyToStartMatch_Implementation TWPlayerState cast fail %s, probably not loaded yet"),*PlayerState->GetClass()->GetName()); //Window->Output Log to show log
			return false;
		}
		
	}
	UE_LOG(YourLog, Warning, TEXT("ATWGameMode::ReadyToStartMatch_Implementation clients are ready")); //Window->Output Log to show log

	if (!TeamSetupDone)
	{
		TeamSetupDone = TWGameState->ServerSetupTeamInfo();
		return TeamSetupDone;
	}

	return true;
}