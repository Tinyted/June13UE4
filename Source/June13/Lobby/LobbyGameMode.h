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

	UFUNCTION(BlueprintCallable, Category = "MapTravel")
	void ServerTravel();

};
