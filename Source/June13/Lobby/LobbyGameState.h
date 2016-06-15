// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "LobbyPlayerState.h"
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

USTRUCT(BlueprintType)
struct FTeamInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<ALobbyPlayerState *> PlayerStates;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 TeamSize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 TeamID;

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

	UFUNCTION(BlueprintCallable, Category = "Variable")
	void Server_SetCurrentSelectedMap(FMapInfo MapInfo);

	UFUNCTION(BlueprintCallable, Category = "Variable")
	FMapInfo GetCurrentSelectedMap();

	UFUNCTION(BlueprintImplementableEvent)
	void setDefaultSelectedMap();

	UPROPERTY(BlueprintReadOnly, Category = "Variable", Replicated)
	int32 SpectatorTeamID;

	UFUNCTION(BlueprintCallable, Category = "Variable")
	TArray<FTeamInfo> GetTeamInfo();

	UFUNCTION(BlueprintCallable, Category = "Variable")
	void Server_ChangePlayerStateTeamID(ALobbyPlayerState *PlayerState, int32 TeamID);

	UFUNCTION(BlueprintImplementableEvent)
	void OnRep_TeamInfoChanged();

	UFUNCTION(BlueprintImplementableEvent)
	void OnRep_ReadyChanged();

private:
	//use the getters and setters to manipulate for public/protected use
	UPROPERTY(Replicated)
	FMapInfo CurrentSelectedMap;

	//Should be updated whenever selected map is changed
	UPROPERTY(ReplicatedUsing = OnRep_TeamInfoChanged)
	TArray<FTeamInfo> TeamInfos;


};
