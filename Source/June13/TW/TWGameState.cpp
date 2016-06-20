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

void ATWGameState::ServerSetupTeam()
{
	if (HasAuthority())
	{
		UE_LOG(YourLog, Warning, TEXT("ATWGameState::ServerSetupTeam")); //Window->Output Log to show log

		bool blueprint = SetupTeam();
		if (blueprint)
			return; //Done. If more stuff needs to be done in C++ AND in blueprint, considering subclassing TWGameState, and overriding this function and not calling super

		UE_LOG(YourLog, Warning, TEXT("ERROR WARNING, TWGameState's default implementation for ServerSetupTeam_Implementation was used, it has NOTHING BRO")); //Window->Output Log to show log
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("ERROR WARNING, TWGameState's default implementation for ServerSetupTeam_Implementation was used, it has NOTHING BRO"));
		}
	}

}


bool ATWGameState::SetupTeam_Implementation()
{
	return false; //Should always return false for C++, blueprint subclass should return 3
}

void ATWGameState::SetTeamInfos(TArray<FGameTeamInfo> TeamInfos)
{
	UE_LOG(YourLog, Warning, TEXT("ATWGameState::SetTeamInfos")); //Window->Output Log to show log
	for (auto& TeamInfo : TeamInfos)
	{
		UE_LOG(YourLog, Warning, TEXT("ATWGameState::SetTeamInfos-> name:%s ,id:%i"),*TeamInfo.TeamName,TeamInfo.TeamID); //Window->Output Log to show log
	}

	mTeamInfos = TeamInfos;
}

bool ATWGameState::ServerSetupTeamInfo()
{
	if (HasAuthority())
	{
		UE_LOG(YourLog, Warning, TEXT("ATWGameState::ServerSetupTeamInfo")); //Window->Output Log to show log

		if (mTeamInfos.Num() == 0) //check if there is no team data
		{
			UE_LOG(YourLog, Warning, TEXT("ERROR WARNING, TWGameState -> mTeamInfos is Empty")); //Window->Output Log to show log
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("ERROR WARNING, TWGameState -> mTeamInfos is Empty"));
			}
			return false;
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
						UE_LOG(YourLog, Warning, TEXT("Found Team ID %i"), teamID); //Window->Output Log to show log
						if (GEngine)
						{
							GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Found Team ID TeamID %i"), teamID));
						}
						break;
					}
				}
				if (!foundTeamInfo)
				{

					//If not in any of the teams, put it on spectator
					mSpectatorInfos.Add(TWPlayerState);
					APlayerController *PlayerController = Cast<APlayerController>(TWPlayerState->GetOwner());
					PlayerController->StartSpectatingOnly();
					UE_LOG(YourLog, Warning, TEXT("TWGameState -> Can't find TeamID %i, gonna be spectator"), teamID); //Window->Output Log to show log
				}
			}
			else 
			{
				return false;
				UE_LOG(YourLog, Warning, TEXT("TWGameState -> PlayerState cast fail in ServerSetupTeamInfo %s, probably didn't finish loading"), *PlayerState->GetClass()->GetName()); //Window->Output Log to show log
			}
		}
	}
	return true;
}

void ATWGameState::OnRep_TeamInfoChanged_Implementation()
{

}