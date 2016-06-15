// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
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


};
