// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "LobbyGameState.generated.h"

USTRUCT(BlueprintType)
struct FGameModeInfo 
{
	GENERATED_BODY() //For reflection

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString GameModeName;

	/* Example
	/Game/TestGame/TestGameMode.TestGameMode_C
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString GameModeURL;

};

USTRUCT(BlueprintType) //necessary for engine to replicate, require F prefix as required by Engine
struct FMapInfo //https://wiki.unrealengine.com/Structs,_USTRUCTS(),_They're_Awesome
{
	GENERATED_BODY() //For reflection

	//UPROPERTY for replication

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MapName;

	/* Example 
		/Game/TestGame/TestMap
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MapURL;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 TeamCount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 TeamSize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameModeInfo GameModeInfo;
};

/**
 * 
 */
UCLASS()
class JUNE13_API ALobbyGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FMapInfo> MapsAvailable;

	UPROPERTY(BlueprintReadWrite, Replicated)
	FMapInfo CurrentSelectedMap;	

	UFUNCTION(BlueprintImplementableEvent)
	void setDefaultSelectedMap();

	UPROPERTY(BlueprintReadOnly, Category = "Variable", Replicated)
	int32 SpectatorTeamID;
};
