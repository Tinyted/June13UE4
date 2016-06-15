// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */


UCLASS()
class JUNE13_API ALobbyGameMode : public AGameMode
{
	GENERATED_BODY()
	
	ALobbyGameMode(const class FObjectInitializer& ObjectInitializer);
	void SetupMapInfo();
	void InitGameState();

public:
	
	virtual void PostLogin(APlayerController* NewPlayer) override;

	//Return false if can't start game, true if countdown starting
	UFUNCTION(BlueprintCallable, Category = "Game Start")
	bool ServerStartGame();

	//To be moved to private
	UFUNCTION(BlueprintCallable, Category = "MapTravel")
	void ServerTravel();

	void InformServerLocalPlayerControllersOfChanges();

private:
	FTimerHandle ServerTravelTimer;

	int8 TravelTimerCountDown;

	void ServerTravelCountDown();
};
