// Fill out your copyright notice in the Description page of Project Settings.

#include "June13.h"
#include "LobbyPlayerController.h"
#include "LobbyPlayerState.h"


void ALobbyPlayerController::BeginPlayingState()
{
	UE_LOG(YourLog, Warning, TEXT("LobbyPlayerController::BeginPlayingState")); //Window->Output Log to show log

	if (PlayerState) 
	{
		UE_LOG(YourLog, Warning, TEXT("LobbyPlayerController, PlayerState exists")); //Window->Output Log to show log
	}

	OnBeginPlayingState();
}

void ALobbyPlayerController::Server_ReadyPlayer_Implementation()
{
	//Double check it has authority
	if (HasAuthority())
	{
		//Get PlayerState
		ALobbyPlayerState *LobbyPlayerState = Cast<ALobbyPlayerState>(PlayerState);
		if (LobbyPlayerState)
		{
			bool readyStatus = LobbyPlayerState->GetReadyStatus();
			LobbyPlayerState->ReadyPlayer(!readyStatus);
		}
	}
}

//Nothing really to validate for a ready process
bool ALobbyPlayerController::Server_ReadyPlayer_Validate()
{
	return true;
}