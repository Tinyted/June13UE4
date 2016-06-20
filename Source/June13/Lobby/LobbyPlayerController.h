// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "LobbyGameState.h"
#include "LobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class JUNE13_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()

	void BeginPlayingState() override;
	
public:

	UFUNCTION(BlueprintImplementableEvent, Category = "BeginCalls")
	void OnBeginPlayingState();

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, Category = "Variable")
	void Server_ReadyPlayer();

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, Category = "Variable")
	void Server_ChangeTeam(int32 TeamID);

	//Only host should be calling this, client calling will do nothing
	UFUNCTION(BlueprintCallable, Category = "Variable")
	void Server_ChangeMap(FMapInfo MapInfo);
	//Only host should be calling this, client calling will do nothing
	UFUNCTION(BlueprintCallable, Category = "Variable")
	void Server_ChangeMapWithIndex(int32 MapIndex); //Because it's UFUNCTION, can't use C++ overloading

	UFUNCTION(NetMulticast, Reliable)
	void MultiCast_DataChanged();

	//Used for local PlayerControllers to update their UI
	UFUNCTION(BlueprintImplementableEvent, Category = "Data Changed")
	void Local_DataChanged();

	//Only server should call it, client calling will do nothing
	UFUNCTION(BlueprintCallable, Category = "Game Start")
	void Server_StartGame();

private:
	//Used to tell any player controllers that are local for the server that data has been changed
	void ServerPlayerController_DataChanged();

};
