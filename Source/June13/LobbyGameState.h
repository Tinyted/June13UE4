// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "LobbyGameState.generated.h"

USTRUCT() //necessary for engine to replicate, require F prefix as required by Engine
struct FMapInfo //https://wiki.unrealengine.com/Structs,_USTRUCTS(),_They're_Awesome
{
	GENERATED_BODY() //For reflection

	//UPROPERTY for replication

	UPROPERTY()
	FString MapName;

	UPROPERTY()
		int32 TeamCount;

	UPROPERTY()
		int32 TeamSize;

	UPROPERTY()
		TArray<FString> SupportModes;
};

/**
 * 
 */
UCLASS()
class JUNE13_API ALobbyGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	TArray<FMapInfo> MapsAvailable;

	
};
