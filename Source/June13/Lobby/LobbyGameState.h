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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, ReplicatedUsing = OnRep_MapAvailableChanged)
	TArray<FMapInfo> MapsAvailable;

	//Server call only, client calling will do nothing
	void Server_SetCurrentSelectedMap(FMapInfo MapInfo); 
	void Server_SetCurrentSelectedMapWithIndex(int32 MapIndex);

	UFUNCTION(BlueprintCallable, Category = "Variable")
	FMapInfo GetCurrentSelectedMap();

	//GameMode calls this after initing the GameState
	UFUNCTION(BlueprintNativeEvent)
	void SetDefaultSelectedMap();

	UPROPERTY(BlueprintReadOnly, Category = "Variable", Replicated)
	int32 SpectatorTeamID;
	UFUNCTION(BlueprintCallable, Category = "Variable")
	TArray<FTeamInfo> GetTeamInfo();
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRemovePlayerStateFromTeam(ALobbyPlayerState *PlayerState);
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerAddPlayerStateToTeam(ALobbyPlayerState *PlayerState, int32 TeamID);

	UFUNCTION(BlueprintNativeEvent)
	void OnRep_TeamInfoChanged();
	UFUNCTION(BlueprintNativeEvent)
	void OnRep_MapAvailableChanged();
	UFUNCTION(BlueprintNativeEvent)
	void OnRep_MapSelectedChanged();

	void AddPlayerState(APlayerState* PlayerState) override;

private:
	//use the getters and setters to manipulate for public/protected use
	UPROPERTY(ReplicatedUsing = OnRep_MapSelectedChanged)
	FMapInfo mCurrentSelectedMap;

	//Should be updated whenever selected map is changed
	UPROPERTY(ReplicatedUsing = OnRep_TeamInfoChanged)
	TArray<FTeamInfo> mTeamInfos;

	void InformLocalPlayerControllerDataChanged();
};
