// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "LobbyGameState.generated.h"

USTRUCT(BlueprintType) //necessary for engine to replicate, require F prefix as required by Engine
struct FMapInfo //https://wiki.unrealengine.com/Structs,_USTRUCTS(),_They're_Awesome
{
	GENERATED_BODY() //For reflection

	//UPROPERTY for replication

	UPROPERTY(BlueprintReadOnly)
	FString MapName;

	UPROPERTY(BlueprintReadOnly)
	int32 TeamCount;

	UPROPERTY(BlueprintReadOnly)
	int32 TeamSize;

	UPROPERTY(BlueprintReadOnly)
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
	UPROPERTY(BlueprintReadOnly)
	TArray<FMapInfo> MapsAvailable;

	
};
