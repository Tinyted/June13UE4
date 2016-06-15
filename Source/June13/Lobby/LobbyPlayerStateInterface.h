#pragma once

#include "LobbyPlayerStateInterface.generated.h"

UINTERFACE()
class ULobbyPlayerStateInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/*
	To be used for PlayerStates, specifically overriding APlayerState::CopyProperties and copying the necessary info such as TeamID over.
*/

class ILobbyPlayerStateInterface 
{
	GENERATED_IINTERFACE_BODY()

public:
	virtual int32 GetTeamID() = 0; //UE4 code standard advises against using just (int). GameModes should determine what each number represents
	virtual void SetTeamID(int32 TeamID) = 0;
};