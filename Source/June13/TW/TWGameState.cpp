// Fill out your copyright notice in the Description page of Project Settings.

#include "June13.h"
#include "TWGameState.h"
#include "TWPlayerState.h"
#include "Net/UnrealNetwork.h"

//Required for UPROPERTY replication
void ATWGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATWGameState, mTeamInfos);
	DOREPLIFETIME(ATWGameState, mSpectatorInfos);


}

void ATWGameState::ServerSetupTeam_Implementation()
{
	UE_LOG(YourLog, Warning, TEXT("ATWGameState::ServerSetupTeam_Implementation")); //Window->Output Log to show log
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("ATWGameState::ServerSetupTeam_Implementation"));
	}

	bool blueprint = SetupTeam();
	if (blueprint)
		return; //Done. If more stuff needs to be done in C++ AND in blueprint, considering subclassing TWGameState, and overriding this function and not calling super

	UE_LOG(YourLog, Warning, TEXT("ERROR WARNING, TWGameState's default implementation for ServerSetupTeam_Implementation was used, it has NOTHING BRO")); //Window->Output Log to show log

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("ERROR WARNING, TWGameState's default implementation for ServerSetupTeam_Implementation was used, it has NOTHING BRO"));
	}
}

bool ATWGameState::ServerSetupTeam_Validate()
{
	return true;
}


bool ATWGameState::SetupTeam_Implementation()
{
	return false; //Should always return false for C++, blueprint subclass should return 3
}

void ATWGameState::ServerSetupTeamInfo_Implementation()
{
	if (&mTeamInfos || mTeamInfos.Num() == 0) //Checks if there is a mTeamInfos by the pointer, and then check if there is no team data
	{
		UE_LOG(YourLog, Warning, TEXT("ERROR WARNING, TWGameState -> mTeamInfos is Empty or NULL")); //Window->Output Log to show log
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("ERROR WARNING, TWGameState -> mTeamInfos is Empty or NULL"));
		}
		return;
	}

	//Loop through the PlayerStates, and determine who is on what team
	for (auto& PlayerState : PlayerArray)
	{
		ATWPlayerState *TWPlayerState = Cast<ATWPlayerState>(PlayerState);
		if (TWPlayerState)
		{
			int32 teamID = TWPlayerState->GetTeamID();
			bool foundTeamInfo = false;
			for (auto& TeamInfo : mTeamInfos)
			{
				if (TeamInfo.TeamID == teamID)
				{
					TeamInfo.PlayerStates.Add(TWPlayerState); //Add PlayerState to the corresponding team
					foundTeamInfo = true;
					break;
				}
			}
			if (!foundTeamInfo)
			{
				//If not in any of the teams, put it on spectator
				mSpectatorInfos.Add(TWPlayerState);
				TWPlayerState->bIsSpectator = true; //Set it as spectator

				UE_LOG(YourLog, Warning, TEXT("ERROR WARNING, TWGameState -> Can't find TeamID %i"),teamID); //Window->Output Log to show log
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("ERROR WARNING, TWGameState -> Can't find TeamID %i"),teamID));
				}
			}
		}
	}
}

bool ATWGameState::ServerSetupTeamInfo_Validate()
{
	return true;
}

void ATWGameState::OnRep_TeamInfoChanged_Implementation()
{

}