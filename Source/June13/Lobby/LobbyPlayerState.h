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

	void CopyProperties(APlayerState* PlayerState) override;
	//Team ID related
	UFUNCTION(BlueprintCallable, Category = "Variable")
	int32 GetTeamID();
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Variable")
	void SetTeamID(int32 TeamID);
	UFUNCTION(BlueprintNativeEvent)
	void OnRep_TeamIDChanged();

	//Ready related
	UFUNCTION(BlueprintCallable, Category = "Variable")
	bool GetReadyStatus();
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Variable")
	void ReadyPlayer(bool ready);
	UFUNCTION(BlueprintNativeEvent)
	void OnRep_ReadyChanged();


protected:
	UPROPERTY(ReplicatedUsing = OnRep_TeamIDChanged)
	int32 mTeamID;

	//See https://docs.unrealengine.com/latest/INT/Gameplay/Networking/CharacterMovementComponent/ for possible client-side prediction (maybe can use simpler method)
	UPROPERTY(ReplicatedUsing = OnRep_ReadyChanged) //Should consider having client see ready status first, before asking the server to replicate it to client, Since 'Replicated' implys Server-owned
	bool mReady;
	
	
};
