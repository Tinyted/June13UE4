// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "TWPlayerState.h"
#include "TWGameState.generated.h"


USTRUCT(BlueprintType)
struct FGameTeamInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<ATWPlayerState *> PlayerStates;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 TeamSize;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 TeamID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString TeamName;
};

/**
 *  TODO: Implement an abstract class or interface as TWGameState uses same/similar things as LobbyGameState
 */
UCLASS()
class JUNE13_API ATWGameState : public AGameState
{
	GENERATED_BODY()
	
public:

	//Used to setup mTeamInfo's size, id name. Override this method for any c++ subclass, or for blueprints implement it via SetupTeam()
	UFUNCTION(Server, Reliable, WithValidation, Category = "Variable")
	void ServerSetupTeam();

	//Should never be called directly, ServerSetupTeam() will call this at the end, ensuring it is done on the server. Return true if used.
	UFUNCTION(BlueprintNativeEvent, Category = "Variable")
	bool SetupTeam();

	//Used to add/remove PlayerState in mTeamInfo
	UFUNCTION(Server, Reliable, WithValidation, Category = "Variable")
	void ServerSetupTeamInfo();

	UFUNCTION(BlueprintNativeEvent)
	void OnRep_TeamInfoChanged();
	
private:
	//Used to store info regarding Playing Teams
	UPROPERTY(ReplicatedUsing = OnRep_TeamInfoChanged)
	TArray<FGameTeamInfo> mTeamInfos; //Can't use * since there's UPROPERTY, and * is not supported

	//Used to store array of PlayerStates that are spectators
	UPROPERTY(ReplicatedUsing = OnRep_TeamInfoChanged)
	TArray<ATWPlayerState *> mSpectatorInfos;
};
