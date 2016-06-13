// Fill out your copyright notice in the Description page of Project Settings.

#include "June13.h"
#include "LobbyPlayerController.h"


void ALobbyPlayerController::BeginPlayingState()
{
	UE_LOG(YourLog, Warning, TEXT("LobbyPlayerController::BeginPlayingState")); //Window->Output Log to show log

	if (PlayerState) 
	{
		UE_LOG(YourLog, Warning, TEXT("LobbyPlayerController, PlayerState exists")); //Window->Output Log to show log
	}

	OnBeginPlayingState();
}