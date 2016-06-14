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

	UFUNCTION(BlueprintCallable, Category = "Variable")
	int32 GetTeamID();

	void CopyProperties(APlayerState* PlayerState) override;

	UFUNCTION(BlueprintCallable, Category = "Variable")
	void SetTeamID(int32 TeamID);

protected:
	UPROPERTY(Replicated)
	int32 mTeamID;
	
	
};
